# Flappy Bird - SFML Version
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

### File structure:
* main.cpp → Main game logic (bird physics, pipe generation, collision detection, rendering)
* Makefile → Build system configuration

## How to play the game
### Debugging:
Creates flappy_bird executable ("make" is called again for debug with every code change)
```
make
```

### Running the game:
```
./flappy_bird
```

### Cleaning the build files (if needed):
```
make clean
```

### Controls:
* Space → Start the game / Make the bird jump
* P → Pause / Resume the game
* R → Restart after game ove
* Q → Quit the game

## Screenshots from the game
![Ekran görüntüsü 2025-04-28 133512](https://github.com/user-attachments/assets/f8dc1043-b968-41df-a370-1a832bef6381)
![Ekran görüntüsü 2025-04-28 133542](https://github.com/user-attachments/assets/d7c1771f-4a5c-44d9-affe-64f0652f121e)
![Ekran görüntüsü 2025-04-28 133608](https://github.com/user-attachments/assets/f0d2a05a-bd58-491a-9a9b-1040c183b272)
![Ekran görüntüsü 2025-04-28 133550](https://github.com/user-attachments/assets/5eadef2f-baa1-4569-9133-b0cc9beee20e)
