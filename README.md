Zombie vs Robot (SFML)
Description
Zombie vs Robot is a 2D platformer game developed in C++ using the SFML library. The player
controls a zombie whose objective is to reach the platform located at the upper-left side of the level
while avoiding enemy robots and falling off the map. The project focuses on core platformer
mechanics such as gravity, tile-based collision detection, enemy spawning systems, and basic
game state management.
Controls
- Left Arrow: Move left
- Right Arrow: Move right
- Space Bar: Jump
Gameplay Rules
The zombie loses a life when colliding with a robot enemy or falling off the level. After five deaths,
the game displays a 'You Lose' message and closes automatically after five seconds. Reaching the
goal area displays a 'You Win' message and also closes the game after five seconds.
Technical Features
- Tile-based collision system using CollisionMap
- Gravity and physics-based movement
- Sprite sheet animation using frame arrays
- Enemy AI with edge detection
- SpawnPool system for enemy reuse
- TimedSpawner for enemy spawning control
Build Instructions
The project is built from scratch using CMake and requires a C++17 compatible compiler and the
SFML library. Compiled binaries and temporary build files are not included in the repository.
