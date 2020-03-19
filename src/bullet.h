#ifndef __BULLET_AGENT__H
#define __BULLET_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BulletController : public Process, public AgentInterface {

    public:
    BulletController() : Process(), AgentInterface(), counter(0) {}

    void init() {
        // Bullet will dispear after hitting on a ghost.
        notice_collisions_with("Gosht", [&](Event &e) {
            remove_agent(e.value()["id"]);
            remove_agent(id());
        });  
                      
    }
    void start() {}
    void update() {
        // After certain range of the distance, bullet will dispear.  
        if ( counter++ > 15 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    double counter;

};

class Bullet : public Agent {
    public:
    Bullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BulletController c;
};

DECLARE_INTERFACE(Bullet)

#endif