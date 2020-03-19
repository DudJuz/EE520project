#ifndef __GOAL_AGENT__H
#define __GOAL_AGENT__H 

#include "enviro.h"

using namespace enviro;
// Goal class is mainly used for a sign to show where the exit point
// for the user. ""Good work!" will show up when mision completed.
class GoalController : public Process, public AgentInterface {

    public:
    GoalController() : Process(), AgentInterface() {}

    void init() {   
            notice_collisions_with("Player", [&](Event &e) {
            
            label("Good work!!\n"
                "Good work!!!\n"
                "Good work!!!",
                (-rand()% num) + 100,rand()%100);
        });          
    }
    void start() {}
    void update() {
    }
    void stop() {}
    const int num = 100.0; 

};

class Goal : public Agent {
    public:
    Goal(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    GoalController c;
};

DECLARE_INTERFACE(Goal)

#endif