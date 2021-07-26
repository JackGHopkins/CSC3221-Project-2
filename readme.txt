# CSC3095-Dissertation

## CSC3221 AABB & Circle Collisions : December 2020 - January 2021

## GitHub Repository: https://github.com/JackGHopkins/CSC3221-Project-2

Used OS: Windows 10

Used Library/Middleware: N/A

Used Engine: N/A

Used Development Environment: Visual Studio Community 2019 | Version 16.3.7

## Why did you create this program?
It was for a University module. The goal was to program a simulation where multiple 2d AABB and Circle objects randomly collide into each other, thus, destroying themselves until no shapes are left.

## What were you careful about?
Both AABB and Circle shapes had to inherate from an abstract class and implementing a check for both of them took a little bit of work. Furthermore, working with many vectors made me weary of "Out Of Bound" Errors.

## What did you find difficult?
Programming in the "Random Game" method, as it took a few tries to cover all the edge cases and program optimsation for collision checking with Spatial Hashing.

## What points do you want us particularly focus on your work?
The `RandomGame()` and Collision.cpp as that is where all the logic for the collisions take place.

## If you took some source codes as reference, what part of them did you use? Please also tell us the filename of that part.
Not applicable. I did not use any source code.

## If you are using a library or function created by someone else, please put those parts in a separate file and write the corresponding filename.
Also, not applicable.

****** IMPORTANT NOTES ******
1st: Explaination for 3D Exention is in the Collisions.cpp file (line
2nd: If Output doesn't look like the Sample Output below, make sure you are not also running the `RandomGame();` in `main();` since it runs by default.


SAMPLE OUTPUT:
***** TESTING: START *****
+++++++++++++++++ COLLISION FOUND +++++++++++++++++
+ Shape No: 00D54E78 | PosX: 0 | PosY: 0 | CellX: 0 | CellY: 0 | Collision: 1 | Size: 10
+ Shape No: 00D5FC90 | PosX: 5 | PosY: 0 | CellX: 0 | CellY: 0 | Collision: 1 | Size: 10

+++++++++++++++++ COLLISION FOUND +++++++++++++++++
+ Shape No: 00D600C8 | PosX: 140 | PosY: 0 | CellX: 1 | CellY: 0 | Collision: 1 | Size: 10
+ Shape No: 00D5FED0 | PosX: 145 | PosY: 0 | CellX: 1 | CellY: 0 | Collision: 1 | Size: 10

+++++++++++++++++ COLLISION FOUND +++++++++++++++++
+ Shape No: 00D5FC00 | PosX: 200 | PosY: 0 | CellX: 2 | CellY: 0 | Collision: 1 | Size: 10
+ Shape No: 00D5FB28 | PosX: 205 | PosY: 0 | CellX: 2 | CellY: 0 | Collision: 1 | Size: 10

+++++++++++++++++ COLLISION FOUND +++++++++++++++++
+ Shape No: 00D5FF18 | PosX: 250 | PosY: 50 | CellX: 2 | CellY: 0 | Collision: 1 | Size: 4
+ Shape No: 00D5FFA8 | PosX: 250 | PosY: 50 | CellX: 2 | CellY: 0 | Collision: 1 | Size: 10

+++++++++++++++++ COLLISION FOUND +++++++++++++++++
+ Shape No: 00D5FDB0 | PosX: 200 | PosY: 50 | CellX: 2 | CellY: 0 | Collision: 1 | Size: 10
+ Shape No: 00D5FD20 | PosX: 200 | PosY: 50 | CellX: 2 | CellY: 0 | Collision: 1 | Size: 5

+++++++++++++++++ COLLISION FOUND +++++++++++++++++
+ Shape No: 00D5FFF0 | PosX: 330 | PosY: 33 | CellX: 3 | CellY: 0 | Collision: 1 | Size: 36
+ Shape No: 00D602F0 | PosX: 310 | PosY: 10 | CellX: 3 | CellY: 0 | Collision: 1 | Size: 20

No. Shapes Remaining:4
+++++++++++++++++ COLLISION FOUND +++++++++++++++++
+ Shape No: 00D5FA98 | PosX: 90 | PosY: 0 | CellX: 0 | CellY: 0 | Collision: 1 | Size: 10
+ Shape No: 00D5FA50 | PosX: 90 | PosY: 0 | CellX: 0 | CellY: 0 | Collision: 1 | Size: 10

+++++++++++++++++ COLLISION FOUND +++++++++++++++++
+ Shape No: 00D5FB70 | PosX: 260 | PosY: 0 | CellX: 2 | CellY: 0 | Collision: 1 | Size: 10
+ Shape No: 00D5FCD8 | PosX: 260 | PosY: 0 | CellX: 2 | CellY: 0 | Collision: 1 | Size: 10

No. Shapes Remaining:0
***** TESTING: END *****
------------------------
