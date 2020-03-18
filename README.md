# Maza challenging - EE P 520


Project Statement
---
This repository is constructed for a maze challenging and containing the full implementation of a project for the EEP 520 course; Software Engineering for Embedded Applications offered at the University of Washington. The project consists of a player robot that controlled by users to seek the exit path of the maze, the ghosts wandering around and trying to catch the player robot and exit point marked in red paint. More detail of the gaming feature will be explained in the functionality section. This project is based on 'Elma' and 'Enviro packages made by Prof.Eric Klavins.

Preparement - MacOS & Windows
---
Although different operating system will take have diferent instruction, this project can function properply on MacOS and Windows enviroment.
First, user will be required to install 'git' in the computer.<br />
Mac
- Install the Xcode Command Line Tools. These tools include git.<br />
Windows
- Go to [https://git-scm.com/download/win](https://git-scm.com/download/win)
Then create a directory for this repository in your computer and make it your working directory. Clone this repository into your computer directory by running:
```bash
git clone https://github.com/DudJuz/EE520projec.git
cd EEP520-FinalProject
```
All the contents should be successfully clone in your computer. <br />
<br />
Preparement - Elma & Enviro
---
As mentioned before, this project is mainly implemented by using Elma & Enviro. The detail documentatiosn of these two packages is in the links below: <br/><br />
Elma    (https://github.com/klavinslab/elma)<br />
Enviro  (https://github.com/klavinslab/enviro) <br /> <br />
For the effective and efficient purpose, it's recommand to install docker to set up the developing enviroment with Elma & Enviro. (https://www.docker.com).  Once completed the installation, go to the directory where the project has been copied and simply do on the terminal window/ powershell for Windows users. <br /> 
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.6 bash
```
Your terminal should be running under "root@...", which means you're working from within the container.<br />
<br />
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
Once compeleted, open your web-browser and type in "http://localhost" which can lead you into the game simulation. 

To manually control the prisoner (circled robot) use keys `W` for moving up, `S` for down, `A` for left, `D` for right, and space-key " " to shoot a bullet.
The simulation can be stopped at any time by using `ctrl + c` in the terminal. If need to re-run the simulation, simply run `enviro` in the terminal. 

Porject Functionality
===

Player Robot
---

Ghosts
---

Goal
---

Key Development Challebges
===

