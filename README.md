This is a game inspired from Plants Vs. Zombies that is implemented purely in C++ and built on top of OpenGL, using various libraries like GLUT and GLEW.
The gameplay is as follows:
- There are 4 types of enemies (represented by the Enemy.cpp class) than can spawn on 3 different lines, continously and randomly.
- As the player, our job is to prevent the enemies from reaching the end of the line by adding plants (represented by Fighter.cpp class).
- Each plant has a specific cost that has to be paid in order to be able to place it on one of the tiles.
- The  only way to accumulate more money is by collecting sun shines than randomly spawn and fall down from the sky.
- On the top right corner of the screen, the player is displayed his remaining lives (the game starts with 3 & ends when it reaches 0) and also the money he has left.
- Every time an enemy reach the end of a line, a heart disappears.




