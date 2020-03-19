#ifndef __PLAYER_AGENT__H
#define __PLAYER_AGENT__H 

#include "enviro.h"
#include "elma/elma.h"
#include <chrono>

using namespace enviro;
using namespace elma;
using namespace std::chrono;

// directional controls and player features including teleport, 
//get caught by the ghost, bullet,showing label when reaches end point.
class PlayerController : public Process, public AgentInterface {
    public:
    PlayerController() : Process(), AgentInterface(), f(0), tau(0), firing(false) {}

    void init() {
        //This watch is looking for user input on if shooting bullet 
        //and directional control.
        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == " " && !firing ) {
                  Agent& bullet = add_agent("Bullet", 
                    x() + 17*cos(angle()), 
                    y() + 17*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    bullet.apply_force(50,0);
                  firing = true;
            } else if ( k == "w" ) {
                  f = magnitude + speedup;              
            } else if ( k == "s" ) {
                  f = -magnitude;  
            } else if ( k == "a" ) {
                  tau = -magnitude;
            } else if ( k == "d" ) {
                  tau = magnitude;
            } 
            else if ( k != "l" ) {
                  speedup = 0;
            } 
            
        }); 
        //Robot control.
        //This watch is lookring for fire status and key press input from users.         
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == " " ) {
                firing = false;
            } else if ( k == "w" || k == "s" ) {
                  f = 0;               
            } else if ( k == "a" ) {
                  tau = 0;
            } else if ( k == "d" ) {
                  tau = 0;
            } 
            else if ( k == "l" ) {
                  speedup = rand()%100;
            } 
            
        });
        // Robot will be teleported to the starting position when collides
        // with ghost. The appearance of robot will be different and movement will
        // be slow by random factor.
        notice_collisions_with("Ghost", [&](Event &e) {
            teleport(-700,350,0);
            decorate("<circle cx=0 cy=0 r=8 style='fill:red'></circle>");
            double magnitude = magnitude - rand()%100;
            
        });  
        //Robot will be teleported to the starting point."You made it" will be
        // display randomly on the screen. The infection effect will dispear. 
        notice_collisions_with("Goal", [&](Event &e) {
            label("You made it!!",-650,350);
            teleport(-700,350,0);
            decorate("");
        }); 
        zoom(2.5);
        
    }
    void start() { }
    void update() {
        apply_force(f,tau);
    } 
    void stop() {}
    double f, tau;
    double magnitude = 180;
    double speedup = 0;
    bool firing;
    const json BULLET_STYLE = { 
                   {"fill", "green"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "5px"},
                   {"strokeOpacity", "0.25"}
               };

};

class Player : public Agent {
    public:
    Player(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    high_resolution_clock::time_point t1,t2;
    PlayerController c;
};

DECLARE_INTERFACE(Player)

#endif