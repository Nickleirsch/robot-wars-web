#ifndef SIMULATION_H
#define SIMULATION_H

#include "../../Robots.h"
#include "../../RobotList.h"
#include "../../RobotQueue.h"
#include "../../Map.h"

#include <string>
#include <memory>

// Simulation is a thin driver around the existing C++ engine. It does the same
// work Main.cpp does, except the turn loop lives in the caller (the browser)
// rather than in here, and every turn's output is captured into a string
// instead of being written to cout / battlefield.txt.
class Simulation
{
private:
    Map* map;
    RobotList list;
    RobotQueue queue;

    int totalSteps;   // "steps:" from the config file
    int turnNumber;   // turns completed so far
    bool ready;       // init() succeeded
    bool finished;    // ran out of steps, or one robot left standing
    string lastLog;   // action log produced by the most recent step()
    string lastError;

    void teardown();

public:
    Simulation();
    ~Simulation();

    // Parses the same .txt format the desktop program reads. Returns false and
    // sets error() if the config is malformed or names an unknown robot type.
    bool init(const string& configText, unsigned int seed);

    // Runs one full turn (traverse -> remove -> dequeue). Returns false when
    // the simulation has already ended.
    bool step();

    string snapshot() const; // full state as JSON
    string log() const { return lastLog; }
    string error() const { return lastError; }
};

#endif
