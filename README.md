# Maza challenging - EE P 520


Project Statement
---
This repository is constructed for a maze challenging and containing the full implementation of a project for the EEP 520 course; Software Engineering for Embedded Applications offered at the University of Washington. The project consists of a player robot that controlled by users to seek the exit path of the maze, the ghosts wandering around and trying to catch the player robot and exit point marked in red paint. More detail of the gaming feature will be explained in the functionality section. This project is based on 'Elma' and 'Enviro packages made by Prof.Eric Klavins.

Preparation - macOS & Windows
---
Although the different operating systems will take have different instructions, this project can function properly on the macOS and Windows environment.First, user will be required to install 'git' in the computer.<br />
Mac
- Install the Xcode Command Line Tools. These tools include git.<br />
Windows
- Go to [https://git-scm.com/download/win](https://git-scm.com/download/win)
Then create a directory for this repository on your computer and make it your working directory. Clone this repository into your computer directory by running:
```bash
git clone https://github.com/DudJuz/EE520projec.git
cd EEP520-FinalProject
```
All the contents should be successfully cloned on your computer. <br />

Preparation - Elma & Enviro
---
As mentioned before, this project is mainly implemented by using Elma & Enviro. The detail documentation of these two packages is in the links below: <br/><br />
Elma    (https://github.com/klavinslab/elma)<br />
Enviro  (https://github.com/klavinslab/enviro) <br /> <br />
For the effective and efficient purpose, it's recommended to install docker to set up the developing environment  with Elma & Enviro. (https://www.docker.com).  Once completed the installation, go to the directory where the project has been copied and simply do on the terminal for MacOS/ PowerShell  for Windows. <br /> 
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.6 bash
```
Your terminal should be running under "root@...", which means you're working from within the container.<br />

Usage
---
The game is designed to control a trapped robot in the maze where surrounding with orange ghosts who are capable to teleport the robot to the start point if a collision happens. As a player/user, you can use the keyboard to control the direction of the robot to navigate the robot to the exit point or even shoot the ghosts with bullets. Let's help this poor robot get out of this maze. <br />
To start this game, you need to do the following comments in your terminal/ powershell. <br /> 
```bash
cd EE520projec
esm start
make
enviro
```
Once completed, open your web browser and type in "http://localhost" which can lead you into the game simulation. 

To manually control the prisoner (circled robot) use keys `W` for moving up, `S` for down, `A` for left, `D` for right, and space-key '""' to shoot a bullet.
The simulation can be stopped at any time by using `ctrl + c` in the terminal. If users need to re-run the simulation, simply run `enviro` in the terminal. 

Porject Functionality
===
Player Robot
---
Player robot is marked in green and controlled by users. All the features or controls are in "PlayerController" under the 'player.h' file.  PlayerController class defines what the robot should do when pressing the keys on the keyboard and at what force / direction should the robot move when the keys are pressed. The class is also counting teleport event of collision if the robot collides with any ghost in the maze. The source code of PlayerController is provided below.  
```c++
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

```

Ghosts
---
The ghosts are marked in the color of orange and wandering randomly in the maze that trying to catch the player robot. The code for the ghost is called 'ghost.h'. The wandering feature is achieved by the omni damper movement. <br />

Goal
---
The goal is the exit point of the maze, marked in the color of red. When robot goes to the exit point, "You made it!!" will label on the screen. Meanwhile, the other teleport event will be triggered  that teleport the robot to the start position.<br /> 

Key Development Challenges
===
This project is one of the most interesting and hand-on projects but I still had several difficult times to conquer some features including maze development, control optimization and ghost featuring. <br />

-Maze Development: Constructing  this maze spent 40% of the time on this project. I first tried to draw a rough sketch on a paper and then I realized it is extremely difficult to put coordination and shape correctly in code. In the end, I used AutoCAD to draw the maze I wanted and get all the coordination accurately. Maze development definitely is a challenge.

