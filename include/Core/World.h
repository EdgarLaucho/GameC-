#pragma once

#include <cstdint>

class Character;
class CollisionMap;
class Robot;

namespace sf
{
	class RenderWindow;
}

namespace tmx
{
	class Map;
}

class MapLayer;

class World
{
	public:

		~World();

		// TO-DO: Ideally the scene should be read from file.
		bool load();

		// To-Do: Implement a unload()

		void update(uint32_t deltaMilliseconds);
		void render(sf::RenderWindow& window);

	private:

		// This is just an example. Think a good way to group the actors of your game. If they need any type of manager, etc...
		Character* m_character{ nullptr };
		Robot* m_robot{ nullptr };

		// To-Do: This should be in its own class, something like "Level" should work
		tmx::Map* m_map{ nullptr };
		CollisionMap* m_collisionMap{ nullptr };
		MapLayer* m_layerZero{ nullptr };
		MapLayer* m_layerOne{ nullptr };
		MapLayer* m_layerTwo{ nullptr };
};