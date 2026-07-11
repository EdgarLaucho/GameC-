#include <Core/AssetManager.h>
#include <Core/World.h>
#include <Core/CollisionMap.h>
#include <Gameplay/GameObject.h>
#include <Gameplay/Zombie.h>
#include <Gameplay/Robot.h>
#include <Render/SFMLOrthogonalLayer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <tmxlite/Map.hpp>

World::~World()
{
	delete m_character;
	delete m_layerZero;
	delete m_layerOne;
	delete m_layerTwo;
	delete m_collisionMap;
	delete m_map;
}

std::unique_ptr<GameObject> World::createRobot(const sf::Vector2f& position)
{
	Robot* robot = Robot::createRobot(position, m_collisionMap);
	return std::unique_ptr<GameObject>(robot);
}

void World::resetRobot(GameObject& object, const sf::Vector2f& position)
{
	static_cast<Robot&>(object).respawn(position);
}

bool World::load()
{
	m_map = new tmx::Map();
	if(!m_map->load("../Data/Levels/demo.tmx"))
	{
		return false;
	}

	m_collisionMap = new CollisionMap(*m_map, 0);

	m_robotPool.init([this](const sf::Vector2f& position) { return this->createRobot(position); }, &World::resetRobot);
	
	m_character = Zombie::createZombie({ 100.f, 620.f }, m_collisionMap);
	if (!m_character)
	{
		return false;
	}
	

	m_layerZero = new MapLayer(*m_map, 0);
	m_layerOne = new MapLayer(*m_map, 1);
	m_layerTwo = new MapLayer(*m_map, 2);
	
	m_robotSpawner.setSpawnPoints({ {530.f, 620.f}, {900.f, 580.f}, {1300.f, 550.f}, {1300.f,350.f},{1300.f,100.f}, { 900.f,25.f } });
	m_robotSpawner.SetIntervalRange(0.5f, 1.5f);
	m_robotSpawner.setMaxAlive(6);
	m_robotSpawner.setLifetimeRange(4.0f,8.0f);
	m_robotSpawner.setEnabled(true);

	m_goalArea = sf::FloatRect(0.f, 0.f, 550.f, 420.f);
	return true;
}

void World::update(uint32_t deltaMilliseconds)
{
	if (m_hasWon || hasLost())
		return;

	m_layerZero->update(sf::milliseconds(deltaMilliseconds));

	if (m_character)
		m_character->update(static_cast<float>(deltaMilliseconds));

	m_robotSpawner.update(static_cast<float>(deltaMilliseconds), m_robotPool);
	m_robotPool.updateAll(static_cast<float>(deltaMilliseconds));

	Zombie* zombie = dynamic_cast<Zombie*>(m_character);
	if(zombie && zombie->isDead())
	{
		m_hasLost = true;
		return;
	}
	if (zombie)
	{
		const sf::FloatRect zb = zombie->getBounds();
		if (zb.intersects(m_goalArea)) 
		{
			m_hasWon = true;
			return;
		}
		for (const auto& up : m_robotPool.getObjects())
		{
			GameObject* obj = up.get();
			if (!obj || !obj->isActive()) continue;

			if (obj->getBounds().intersects(zb))
			{
				zombie->takeHit();

				if (!zombie->isDead())
				{
					zombie->respawnAtStart();
				}
				else
				{
					m_hasLost = true;
				}
				break;
			}
			
		}
	}

	
}

void World::render(sf::RenderWindow& window)
{
	window.draw(*m_layerZero);
	window.draw(*m_layerOne);
	window.draw(*m_layerTwo);
	if (m_character)
		m_character->render(window);
	m_robotPool.renderAll(window);
}
