# OpenGL Circuit Race Project
This project is a simple race game in which you can control a car and drive it around a circuit. This game was developped as part of the IG (Informatique Graphique) class taught in the 1st year of Master's degree in Computer Science at the Université de Franche-Comté.

### Build
This project is made to run on Windows 7 or above using Visual Studio. Open `Projet.sln` with Visual Studio and run it from there using the debugging tool. The only requirement is for `glut32.dll` to be placed in `C:\Windows\System32` or in the `Bin` folder of this project.

### Structure
```
|-Bin/
|-Include/
| |-GL/
| |-Billboard.h
| |-Bleachers.h
| |-BoundingBox.h
| |-Checker.h
| |-Crowd.h
| |-Grid.h
| |-Object.h
| |-Patch.h
| |-Position.h
| |-RacingCar.h
| |-Spectator.h
| |-StraightLine.h
| |-TrackPart.h
| |-Tree.h
| |-Turn.h
|-Lib/
|-Meta/
|-Projet/
| |-Projet.sln
|-Src/
| |-BRT.cpp
| |-Billboard.cpp
| |-Bleachers.cpp
| |-BoundinBox.cpp
| |-Checker.cpp
| |-Crowd.cpp
| |-Grid.cpp
| |-Main.cpp
| |-Object.cpp
| |-Patch.cpp
| |-Position.cpp
| |-RacingCar.cpp
| |-Spectator.cpp
| |-StraightLine.cpp
| |-TrackPart.cpp
| |-Tree.cpp
| |-Turn.cpp
|-Temp/
|-README.md
```

### Controls
Use **Enter Key** to start playing.

Use **Arrow Keys** to move the car forward, left, right and backward.

Use **Space Bar** for hand braking.

At any moment, press **R** to restart.

### Authors
- Nicolas Bouchard;
- Timothée Guy;
- Timothée Laurent.
