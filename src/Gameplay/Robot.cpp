#include <Gameplay/Robot.h>
#include <core/AssetManager.h>
#include <core//CollisionMap.h>
#include <SFML/Graphics/Texture.hpp>

Robot* Robot::create(const sf::Vector2f& postion, CollisionMap* collisionMap)
{
	sf::Texture* robotTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Robot.png");

	Robot::RobotDescriptor robotDescriptor;
	robotDescriptor.texture = robotTexture;
	robotDescriptor.position = postion;
	robotDescriptor.speed = { 100.f };
	robotDescriptor.tileWidth = 192.f/2.f;
	robotDescriptor.tileHeight = 256.f/2.f;
	Robot* robot = new Robot();

	if (!robot->init(robotDescriptor))
	{
		delete robot;
		return nullptr;
	}

	robot->setCollisionMap(collisionMap);
	return robot;
}

bool Robot::init(const RobotDescriptor& robotDescriptor)
{
	bool ok = Character::init(robotDescriptor);
	
	int spriteWidth = 32;
	int spriteHeight = 32;

	m_sprite.setScale(1.f,1.f);
	m_speed = robotDescriptor.speed;
	m_direction = 1;
	return ok;
}

void Robot::setCollisionMap(CollisionMap* collisionMap) 
{
	Character::setCollisionMap(collisionMap);
}

void Robot::update(float deltaMilliseconds) 
{
	if (!m_collisionMap) return;

	float dt = deltaMilliseconds / 1000.f;
	gravity(deltaMilliseconds, 2000.f);

	float move = m_direction * m_speed * dt;
	sf::Vector2f newPos = m_position;
	newPos.x += move;

	auto tileSize = m_collisionMap->getTileSize();

	float scaledWidth = m_tileWidth * m_sprite.getScale().x;
	float scaledHeight = m_tileHeight * m_sprite.getScale().y;

	
	float footInset = 28.f;

	
	float feetY = (m_position.y + scaledHeight + 1.f);

	
	float leftFootX = newPos.x + footInset;
	float rightFootX = newPos.x + scaledWidth - footInset;

	
	int tileBelowLeftX = static_cast<int>(leftFootX / tileSize.x);
	int tileBelowRightX = static_cast<int>(rightFootX / tileSize.x);
	int tileBelowY = static_cast<int>(feetY / tileSize.y);

	
	int frontFootTileX = (m_direction == 1) ? tileBelowRightX : tileBelowLeftX;

	
	if (!m_collisionMap->isSolid(frontFootTileX, tileBelowY))
	{
		m_direction *= -1;

		m_position.x += m_direction * 2.f;
	}



	
	m_position.x += m_direction * m_speed * dt;

	Character::update(deltaMilliseconds);
}
