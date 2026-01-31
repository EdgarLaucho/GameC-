#pragma once

#include <cstdint>
#include <Core/SpawnPool.h>
#include <Core/TimedSpawner.h>
#include <SFML/Graphics/Rect.hpp>
#include <memory>


class Character;
class CollisionMap;
class Robot;
class GameObject;

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
		bool hasWon() const { return m_hasWon; }
		

	private:

		// This is just an example. Think a good way to group the actors of your game. If they need any type of manager, etc...
		std::unique_ptr<GameObject> createRobot(const sf::Vector2f& position);
		static void resetRobot(GameObject& object, const sf::Vector2f& position);
		Character* m_character{ nullptr };
		SpawnPool m_robotPool;
		TimedSpawner m_robotSpawner;

		// To-Do: This should be in its own class, something like "Level" should work
		tmx::Map* m_map{ nullptr };
		CollisionMap* m_collisionMap{ nullptr };
		MapLayer* m_layerZero{ nullptr };
		MapLayer* m_layerOne{ nullptr };
		MapLayer* m_layerTwo{ nullptr };

		sf::FloatRect m_goalArea{ 0.f,0.f,420.f,220.f };
		bool m_hasWon{ false };
};