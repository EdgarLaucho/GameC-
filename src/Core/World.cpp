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

	// To-Do, read ALL from file, this is just a quick example to understand that here is where entities are created but consider grouping/managing actors in a smarter way


	// To-Do, Load level: this should have its own class
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

	m_robotPool.acquire({ 530.f, 620.f });
	m_robotPool.acquire({ 800.f, 620.f });

	return true;
}

void World::update(uint32_t deltaMilliseconds)
{
	m_layerZero->update(sf::milliseconds(deltaMilliseconds));

	if (m_character)
		m_character->update(static_cast<float>(deltaMilliseconds));
	m_robotPool.updateAll(static_cast<float>(deltaMilliseconds));

	
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