#ifndef __GHOST_AGENT__H
#define __GHOST_AGENT__H 

#include "enviro.h"
#include <math.h>

using namespace enviro;
// Ghost will move in omni behavious. Ghost will be gone when hitted by a bullet.
class GhostController : public Process, public AgentInterface {

    public:
    GhostController() : Process(), AgentInterface() {}

    void init() {
        //Adding two eyes on the ghost.
        decorate(R"(<g>
            <circle cx=-5 cy=-3 r=2 style='fill:black'></circle>
            <circle cx=5 cy=-3 r=2 style='fill:black'></circle></g>)");
    }

    void start() {}
    void update() {
        //omni beheavious
        omni_apply_force(
            (rand() % fmax) - fmax/2, 
            (rand() % fmax) - fmax/2
        );
        notice_collisions_with("Bullet", [&](Event &e) {
            remove_agent(id());
        });     
    }
    void stop() {}
    //set the constant fmax
    const int fmax = 100.0;          
};

class Ghost : public Agent {
    public:
    Ghost(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    GhostController c;
};

DECLARE_INTERFACE(Ghost)

#endif
