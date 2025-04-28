# Flappy Bird - SFML(Simple and Fast Multimedia Library) Version
This project is a simple recreation of the classic Flappy Bird game using C++ and the SFML library. It is developed and tested on WSL Ubuntu under Windows.
## Installations
### For the library installation:
```
sudo apt update
sudo apt install libsfml-dev
```

### To fix possible font error problem:
```
sudo apt-get install fonts-dejavu
```
<hr>

### File structure:
* main.cpp → Main game logic (bird physics, pipe generation, collision detection, rendering)
* Makefile → Build system configuration

### Debugging:
Creates flappy_bird executable ("make" is called again for debug with every code change)
```
make
```

### Cleaning the build files (if needed):
```
make clean
```

### Running the game:
```
./flappy_bird
```

### Controls:
* Space → Start the game / Make the bird jump
* P → Pause / Resume the game
* R → Restart after game ove
* Q → Quit the game