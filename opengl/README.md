# Flappy Bird - OpenGL Version
This is a implementation of the classic "Flappy Bird" game using OpenGL, GLFW, GLEW, and GLM libraries. The game consists of a bird that the player controls by pressing the spacebar to make the bird "flap" and avoid obstacles (pipes). The goal is to keep the bird in the air while navigating through the pipes, earning points for each pipe the bird successfully passes.

### Needed Installations
* Before compiling and running the game, make sure to have the necessary libraries installed on your system. The following instructions are for Linux-based systems (Ubuntu). Game is made and tested on WSL-Ubuntu.

```
sudo apt install -y build-essential cmake pkg-config
sudo apt install -y mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
sudo apt install -y libglew-dev libglfw3-dev libglm-dev
```

* On terminal, by using command:
```
glxgears 
```
you can test and verify that you successfully downloaded the OpenGL library. This will display a simple OpenGL rendering window with rotating gears. If the window appears, OpenGL is working correctly.

### Debugging
* In directory /home/.../opengl
```
g++ -o flappy_bird src/main.cpp -lglfw -lGLEW -lGL -lGLU -lglut
```

### Running the game
* Once the program is compiled, you can run the game by executing the following command:
```
./flappy_bird 
```

### How to play
* SPACE: Make the bird flap.
* R: Restart the game after a game over.
* Q: Quit the game.

### Screenshots from the game
![Ekran görüntüsü 2025-04-28 141105](https://github.com/user-attachments/assets/7d287b2b-d18c-464d-8ba0-5bc4afdddbd8)
![Ekran görüntüsü 2025-04-28 141222](https://github.com/user-attachments/assets/efe59978-04bd-4c2f-a4b2-824624aaf0d9)
![Ekran görüntüsü 2025-04-28 141251](https://github.com/user-attachments/assets/32c071d2-563f-4e0a-a2f3-dc02a8aec461)
