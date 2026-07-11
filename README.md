# Zombie vs Robot

2D platformer developed in C++17 with SFML. The player controls a zombie that must reach the goal area while avoiding enemy robots and falling out of the level.

The project focuses on core gameplay programming concepts such as tile-based collision, gravity, sprite animation, enemy spawning and game state management.

## Features

- 2D platformer movement with gravity and jumping.
- Tile-based collision system using Tiled/TMX maps.
- Enemy robots with basic patrol behavior and edge detection.
- Timed enemy spawning with configurable spawn points and lifetime.
- Spawn pool system to reuse enemy instances.
- Win and lose states with on-screen feedback.
- Sprite sheet animation for player and enemies.
- CMake project structure with external dependencies handled through FetchContent.

## Technologies

- C++17
- SFML
- tmxlite
- CMake
- Tiled/TMX maps

## Controls

- Left Arrow: move left
- Right Arrow: move right
- Space: jump

## Gameplay

The zombie loses one life when colliding with a robot or falling off the map. After five hits, the game shows a lose message and closes after a short delay.

The player wins by reaching the goal area located in the upper-left section of the level.

## Build

Requirements:

- CMake 3.16 or newer
- C++17 compatible compiler

Generate and build:

```bash
cmake -S . -B build
cmake --build build
```

On Windows with Visual Studio:

```bash
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build
```

The build process copies the `data` folder into the build directory so the executable can load maps, fonts and textures correctly.

## Portfolio Summary

Zombie vs Robot is a C++/SFML gameplay programming project featuring platformer movement, tile collision, enemy spawning, object pooling, sprite animation and TMX level loading.
