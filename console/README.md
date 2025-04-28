# Flappy Bird - Console Version
* A simple Flappy Bird clone playable directly in the console (terminal).
* Developed in C for WSL Ubuntu(Linux) environment.
* Should work on most Linux distributions with ncurses support.

### Requirements:
Make sure ncurses library is installed:
```
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev
```
## How to start playing
### Debugging:
```
gcc -o flappy_bird flappy_bird.c -lncurses
```

### Running the game:
```
./flappy_bird
```

## How to play
* Press Enter to start the game.
* Press Space to make the bird jump.
* Press P to pause and unpause the game.
* When you lose:
    * Press R to restart the game.
    * Press Q to quit the game.

### Some screenshots from the game:
![Ekran görüntüsü 2025-04-28 131520](https://github.com/user-attachments/assets/c15e2b37-9484-4c8d-b4b2-eab5430b0ad5)
![Ekran görüntüsü 2025-04-28 131642](https://github.com/user-attachments/assets/12f7a3c6-d0c2-43bb-9c1f-02f8e73cfa11)
![Ekran görüntüsü 2025-04-28 131752](https://github.com/user-attachments/assets/63f38ae5-acac-43eb-8642-ce728062dad3)
