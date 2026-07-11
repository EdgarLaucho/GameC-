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

		bool load();

		void update(uint32_t deltaMilliseconds);
		void render(sf::RenderWindow& window);
		bool hasWon() const { return m_hasWon; }
		bool hasLost() const { return m_hasLost; };
		

	private:

		std::unique_ptr<GameObject> createRobot(const sf::Vector2f& position);
		static void resetRobot(GameObject& object, const sf::Vector2f& position);
		Character* m_character{ nullptr };
		SpawnPool m_robotPool;
		TimedSpawner m_robotSpawner;

		tmx::Map* m_map{ nullptr };
		CollisionMap* m_collisionMap{ nullptr };
		MapLayer* m_layerZero{ nullptr };
		MapLayer* m_layerOne{ nullptr };
		MapLayer* m_layerTwo{ nullptr };

		sf::FloatRect m_goalArea{ 0.f,0.f,420.f,220.f };
		bool m_hasWon{ false };
		bool m_hasLost{ false };
};
