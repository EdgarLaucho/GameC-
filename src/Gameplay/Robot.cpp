#include <Gameplay/Robot.h>
#include <Core/AssetManager.h>
#include <Core/CollisionMap.h>
#include <SFML/Graphics/Texture.hpp>

Robot* Robot::createRobot(const sf::Vector2f& postion, CollisionMap* collisionMap)
{
	sf::Texture* robotTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Robot.png");

	Robot::RobotDescriptor robotDescriptor;
	robotDescriptor.texture = robotTexture;
	robotDescriptor.position = postion;
	robotDescriptor.speed = 100.f ;
	robotDescriptor.tileWidth = 96.f;
	robotDescriptor.tileHeight = 128.f;
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
	if(!Character::init(robotDescriptor))
	{
		return false;
	}

	m_sprite.setScale(0.9f,0.9f);
	m_speed = robotDescriptor.speed;
	m_direction = 1;
	return true;
}

void Robot::setCollisionMap(CollisionMap* collisionMap) 
{
	Character::setCollisionMap(collisionMap);
}

void Robot::update(float deltaMilliseconds) 
{
	if (!isActive()) return;
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

		newPos.x = m_position.x + m_direction*2.f;
	}else
	{
		newPos.x = m_position.x + move;
	}

	m_position.x = newPos.x;

	m_animTimer += deltaMilliseconds/1000.f;
	const float frameTime = 0.09f;
	if (m_animTimer >= frameTime)
	{
		m_animTimer -= frameTime;
		n_animFrame = (n_animFrame + 1) % 4;
		const int col = RUN_COLS[n_animFrame];
		const int row = 0;

		m_sprite.setTextureRect(sf::IntRect(col * (int)m_tileWidth, row* (int)m_tileHeight, (int)m_tileWidth, (int)m_tileHeight));
	}

	Character::update(deltaMilliseconds);
}

void Robot::respawn(const sf::Vector2f& position) 
{
	setActive(true);
	m_position = position;
	m_velocity = { 0.f, 0.f };
	m_isOnGround = false;
	m_direction = 1;
	m_sprite.setPosition(m_position);
}
