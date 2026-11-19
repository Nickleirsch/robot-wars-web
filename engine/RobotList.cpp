#include "RobotList.h"
#include "Sentinel.h"
#include "PrimeSentinel.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "BlueThunder.h"
#include "Madbot.h"
#include "RoboTank.h"
#include "UltimateRobot.h"

RobotList::RobotList()
{
    head = nullptr;
    size = 0;
}

RobotList::RobotList(const RobotList& copy) // copy constructor
{
    size = copy.size;
    if (copy.head) 
    {
        int X = copy.head->robot->getX();
        int Y = copy.head->robot->getY();
        string name = copy.head->robot->getName();
        string type = copy.head->robot->getType();
        shared_ptr<Robot> robot = cloneRobot(X, Y, name, type);
        head = make_shared<Node>(robot);
        shared_ptr<Node> current = head;
        shared_ptr<Node> copyCurrent = copy.head->next;

        while (copyCurrent) 
        {
            int X = copyCurrent->robot->getX();
            int Y = copyCurrent->robot->getY();
            string name = copyCurrent->robot->getName();
            string type = copyCurrent->robot->getType();
            shared_ptr<Robot> robot = cloneRobot(X, Y, name, type);
            current->next = make_shared<Node>(robot);
            current = current->next;
            copyCurrent = copyCurrent->next;
        }
    }
}

RobotList& RobotList::operator=(const RobotList& operand) // overloaded assignment operator
{
    if (this == &operand) {
        return *this; // self-assignment
    }

    size = operand.size;
    head.reset(); // clear existing list

    if (operand.head) {
        
        int X = operand.head->robot->getX();
        int Y = operand.head->robot->getY();
        string name = operand.head->robot->getName();
        string type = operand.head->robot->getType();
        shared_ptr<Robot> robot = cloneRobot(X, Y, name, type);
        head = make_shared<Node>(robot);
        shared_ptr<Node> current = head;
        shared_ptr<Node> operandCurrent = operand.head->next;

        while (operandCurrent) {
            int X = operandCurrent->robot->getX();
            int Y = operandCurrent->robot->getY();
            string name = operandCurrent->robot->getName();
            string type = operandCurrent->robot->getType();
            shared_ptr<Robot> robot = cloneRobot(X, Y, name, type);
            current->next = make_shared<Node>(robot);
            current = current->next;
            operandCurrent = operandCurrent->next;
        }
    }

    return *this;
}

void RobotList::insert(shared_ptr<Robot>& robot) {
    shared_ptr<Node> newNode = make_shared<Node>(robot);
    if (head == nullptr) 
    {
        head = move(newNode);
    } 
    else 
    {
        Node* current = head.get();
        while (current->next) 
        {
            current = current->next.get();
        }
        current->next = move(newNode);
    }
    size++;
}

void RobotList::traverse(RobotQueue& queue, ostream& COUT) 
{
    Node* current = head.get();
    while (current) 
    {
        if (current->robot->deathCount > 2) //robot dead
        {
            //robot can't respawn
        }
        else if (current->robot->checkStatus() == false) //robot dead but can respawn
        {
            bool added = queue.enqueue(current->robot);
            if (added)
                current->robot->incrementDeath();
        }
        else if (current->robot->checkStatus() == true)
        { 
        //cout << current->robot->getName() << "'s turn" << endl;
        this->upgrade(current->robot, COUT);
        current->robot->turn(COUT);
        }
        current = current->next.get();
    }

    current = head.get();
    while (current) 
    {
        if (current->robot->checkStatus() == false) //robot dead
        {
            bool added = queue.enqueue(current->robot);
            if (added)
                current->robot->incrementDeath();
        }
        current = current->next.get();
    }

    remove();
}

void RobotList::upgrade(shared_ptr<Robot>& robot, ostream& COUT)
{
   if(robot->getKills() >= 3) //upgrade
   {
      int X = robot->getX();
      int Y = robot->getY();
      char initial = robot->getInitial();
      string name = robot->getName();

      string type = robot->getType();
      if (type == "Terminator" || type == "RoboCop")
      {
         cout << "Upgrading " << name << endl;
         robot = move(make_shared<TerminatorRoboCop>(X, Y, initial, name));
      }
      else if (type == "BlueThunder")
      {
         robot = move(make_shared<Madbot>(X, Y, initial, name));
      }
      else if (type == "Madbot")
      {
         robot = move(make_shared<RoboTank>(X, Y, initial, name));
      }
      else if (type == "RoboTank" || type == "T-RoboCop" )
      {
         robot = move(make_shared<UltimateRobot>(X, Y, initial, name));
      }
      else if (type == "Sentinel")
      {
      robot = move(make_shared<PrimeSentinel>(X, Y, initial, name));
      }
      else
         return;
      cout << "Upgrading " << name << endl;
   }
}

int RobotList::getListSize()
{
    return size;
}
void RobotList::displayStats(ostream& COUT)
{
   COUT << "Robot\t\t| Name\t\t| Icon\t| Kills\t| Deaths" << endl;
   COUT << "-------------------------------------------------------------" <<endl;

   Node* current = head.get();
   while (current) 
   {
      //if (current->robot->deathCount < 3)
      //{
         COUT << current->robot->getType();

         if ((current->robot->getType()).length() < 8)
            COUT << "\t\t|";
         else 
            COUT << "\t|";
         COUT << current->robot->getName();

         if ((current->robot->getName()).length() < 8)
            COUT << "\t\t|";
         else 
            COUT << "\t|";
            COUT << current->robot->getInitial() << "\t| "
            << current->robot->getKills() << "\t| "
            << current->robot->deathCount << endl;
      //}

      current = current->next.get();
   }
   COUT << endl;
}

void RobotList::displayList(ostream& COUT)
{
    COUT << "Linked List : ";
    Node* current = head.get();
        while (current) 
        {
            COUT << current->robot->getName() << " --- ";
            current = current->next.get();
        }
        COUT << endl << endl;
    //current = head.get();
    //cout << size << endl;
}

vector<shared_ptr<Robot>> RobotList::getRobots() const
{
    vector<shared_ptr<Robot>> robots;
    Node* current = head.get();
    while (current)
    {
        robots.push_back(current->robot);
        current = current->next.get();
    }
    return robots;
}

void RobotList::remove()
{
    while (head != nullptr && head->robot->getDeaths() >= 3) //if first in list needs to be removed
    {
        head = head->next;
        size--;
    }

    shared_ptr<Node> current = head;
    shared_ptr<Node> previous = nullptr;

    while (current != nullptr) {
        if (current->robot->getDeaths() >= 3) {
            //remove current node
            if (previous != nullptr) {
                previous->next = current->next;
            } else {
                head = current->next; //update head if the first node removed
            }
            current = previous ? previous->next : head; //move to the next node
            size--;
        } else {
            // move previous ptr
            previous = current;
            // move current ptr
            current = current->next;
        }
    }
}