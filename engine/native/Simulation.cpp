#include "Simulation.h"

#include "../../Sentinel.h"
#include "../../PrimeSentinel.h"
#include "../../RoboCop.h"
#include "../../Terminator.h"
#include "../../TerminatorRoboCop.h"
#include "../../BlueThunder.h"
#include "../../Madbot.h"
#include "../../RoboTank.h"
#include "../../UltimateRobot.h"

#include <sstream>
#include <vector>
#include <cstdlib>

namespace
{
    // Several robot actions log to cout as well as to the stream they are given.
    // In a browser cout lands in the devtools console, so we point it at a sink
    // that discards everything and read the turn log off our own ostringstream.
    class NullBuffer : public streambuf
    {
    protected:
        int overflow(int c) override { return c; }
    };

    void silenceCout()
    {
        static NullBuffer nullBuffer;
        static bool done = false;
        if (!done)
        {
            cout.rdbuf(&nullBuffer);
            done = true;
        }
    }

    // Same dispatch as interpretLine() in Main.cpp, but it reports failure to
    // the caller instead of calling exit(1) -- we cannot kill the browser tab.
    shared_ptr<Robot> makeRobot(string& type, string name, string X, string Y, char initial)
    {
        if (type == "RoboCop")                return make_shared<RoboCop>(X, Y, initial, name);
        if (type == "Terminator")             return make_shared<Terminator>(X, Y, initial, name);
        if (type == "TerminatorRoboCop")
        {
            type = "T-RoboCop"; //shorten the name for display purposes
            return make_shared<TerminatorRoboCop>(X, Y, initial, name);
        }
        if (type == "BlueThunder")            return make_shared<BlueThunder>(X, Y, initial, name);
        if (type == "Madbot")                 return make_shared<Madbot>(X, Y, initial, name);
        if (type == "RoboTank")               return make_shared<RoboTank>(X, Y, initial, name);
        if (type == "UltimateRobot")          return make_shared<UltimateRobot>(X, Y, initial, name);
        if (type == "Sentinel")               return make_shared<Sentinel>(X, Y, initial, name);
        if (type == "PrimeSentinel")          return make_shared<PrimeSentinel>(X, Y, initial, name);
        return nullptr;
    }

    // "M by N : 10 10" -> "10 10", "steps: 30" -> "30". More forgiving than the
    // fixed-width erase() the desktop version uses.
    string afterColon(const string& line)
    {
        size_t colon = line.find(':');
        if (colon == string::npos)
            return line;
        return line.substr(colon + 1);
    }

    string trim(const string& s)
    {
        size_t begin = s.find_first_not_of(" \t\r\n");
        if (begin == string::npos)
            return "";
        size_t end = s.find_last_not_of(" \t\r\n");
        return s.substr(begin, end - begin + 1);
    }

    string jsonEscape(const string& s)
    {
        string out;
        for (char c : s)
        {
            switch (c)
            {
                case '"':  out += "\\\""; break;
                case '\\': out += "\\\\"; break;
                case '\n': out += "\\n";  break;
                case '\r': out += "\\r";  break;
                case '\t': out += "\\t";  break;
                default:
                    if (static_cast<unsigned char>(c) < 0x20)
                    {
                        char buf[7];
                        snprintf(buf, sizeof(buf), "\\u%04x", c);
                        out += buf;
                    }
                    else
                    {
                        out += c;
                    }
            }
        }
        return out;
    }
}

Simulation::Simulation()
    : map(nullptr), totalSteps(0), turnNumber(0), ready(false), finished(false)
{
    silenceCout();
}

Simulation::~Simulation()
{
    teardown();
}

void Simulation::teardown()
{
    list = RobotList();   // drop every node; shared_ptrs release the robots
    queue = RobotQueue();
    delete map;
    map = nullptr;
    Robot::setMap(nullptr);
    ready = false;
}

bool Simulation::init(const string& configText, unsigned int seed)
{
    teardown();
    lastError.clear();
    lastLog.clear();
    turnNumber = 0;
    finished = false;

    srand(seed); //fixed seed makes a run reproducible from the UI

    istringstream config(configText);
    string line;

    // line 1: dimensions
    if (!getline(config, line))
    {
        lastError = "Config is empty.";
        return false;
    }
    int M = 0, N = 0;
    {
        istringstream dims(afterColon(line));
        if (!(dims >> M >> N) || M <= 0 || N <= 0)
        {
            lastError = "Could not read battlefield dimensions from: " + trim(line);
            return false;
        }
    }

    // line 2: steps
    if (!getline(config, line))
    {
        lastError = "Config is missing the 'steps:' line.";
        return false;
    }
    {
        istringstream steps(afterColon(line));
        if (!(steps >> totalSteps) || totalSteps <= 0)
        {
            lastError = "Could not read step count from: " + trim(line);
            return false;
        }
    }

    // line 3: robot count
    if (!getline(config, line))
    {
        lastError = "Config is missing the 'robots:' line.";
        return false;
    }
    int declared = 0;
    {
        istringstream robots(afterColon(line));
        if (!(robots >> declared) || declared <= 0)
        {
            lastError = "Could not read robot count from: " + trim(line);
            return false;
        }
    }

    map = new Map(M, N);
    Robot::setMap(map);

    // Remaining lines: one robot each. The desktop version trusts the declared
    // count and reads blank lines when it is too high (10x10.txt says 9 but
    // lists 7), so we take whichever runs out first.
    int created = 0;
    while (created < declared && getline(config, line))
    {
        string trimmed = trim(line);
        if (trimmed.empty())
            continue;

        string type, name, X, Y;
        istringstream fields(trimmed);
        if (!(fields >> type >> name >> X >> Y))
        {
            lastError = "Malformed robot line: " + trimmed;
            teardown();
            return false;
        }

        char initial = name[0];
        shared_ptr<Robot> robot = makeRobot(type, name, X, Y, initial);
        if (!robot)
        {
            lastError = "Unknown robot type '" + type + "'. Check the spelling.";
            teardown();
            return false;
        }
        list.insert(robot);
        created++;
    }

    if (created == 0)
    {
        lastError = "No robots were listed in the config.";
        teardown();
        return false;
    }

    ready = true;
    return true;
}

bool Simulation::step()
{
    if (!ready || finished)
        return false;

    ostringstream out;

    // Mirrors the body of the turn loop in Main.cpp.
    list.traverse(queue, out);
    queue.dequeue(out);

    turnNumber++;
    lastLog = out.str();

    if (turnNumber >= totalSteps || list.getListSize() <= 1)
        finished = true;

    return true;
}

string Simulation::snapshot() const
{
    ostringstream json;
    json << "{";
    json << "\"turn\":" << turnNumber
         << ",\"totalSteps\":" << totalSteps
         << ",\"finished\":" << (finished ? "true" : "false")
         << ",\"ready\":" << (ready ? "true" : "false");

    if (!ready || map == nullptr)
    {
        json << ",\"rows\":0,\"cols\":0,\"grid\":[],\"robots\":[],\"queue\":[],\"listSize\":0";
        json << ",\"error\":\"" << jsonEscape(lastError) << "\"}";
        return json.str();
    }

    json << ",\"rows\":" << map->M << ",\"cols\":" << map->N;

    // grid[x] is one battlefield row, '.' for empty
    json << ",\"grid\":[";
    for (int x = 0; x < map->M; x++)
    {
        if (x) json << ",";
        string row;
        for (int y = 0; y < map->N; y++)
            row += map->battlefield[x][y];
        json << "\"" << jsonEscape(row) << "\"";
    }
    json << "]";

    json << ",\"robots\":[";
    vector<shared_ptr<Robot>> robots = list.getRobots();
    for (size_t i = 0; i < robots.size(); i++)
    {
        shared_ptr<Robot>& r = robots[i];
        if (i) json << ",";
        json << "{\"name\":\"" << jsonEscape(r->getName()) << "\""
             << ",\"type\":\"" << jsonEscape(r->getType()) << "\""
             << ",\"initial\":\"" << jsonEscape(string(1, r->getInitial())) << "\""
             << ",\"x\":" << r->getX()
             << ",\"y\":" << r->getY()
             << ",\"kills\":" << r->getKills()
             << ",\"deaths\":" << r->getDeaths()
             << ",\"alive\":" << (r->checkStatus() ? "true" : "false")
             << "}";
    }
    json << "]";

    json << ",\"queue\":[";
    vector<string> queued = queue.getNames();
    for (size_t i = 0; i < queued.size(); i++)
    {
        if (i) json << ",";
        json << "\"" << jsonEscape(queued[i]) << "\"";
    }
    json << "]";

    json << ",\"listSize\":" << const_cast<RobotList&>(list).getListSize();
    json << ",\"error\":\"" << jsonEscape(lastError) << "\"";
    json << "}";
    return json.str();
}
