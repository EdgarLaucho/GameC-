#include <Gameplay/Zombie.h>
#include <Core/AssetManager.h>
#include <Core/CollisionMap.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Zombie* Zombie::createZombie(const sf::Vector2f& postion, CollisionMap* collisionMap)
{
	sf::Texture* zombieTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/zombie.png");
	Zombie::ZombieDescriptor zombieDescriptor;
	zombieDescriptor.texture = zombieTexture;
	zombieDescriptor.position = postion;
	zombieDescriptor.speed = { 200.f , .0f }; // 400 units per second, or 0.4 units per millisecond, using the latter so it's in alignment with delta time
	zombieDescriptor.tileWidth = 192.f;
	zombieDescriptor.tileHeight = 256.f;

	Zombie* zombie = new Zombie();

	if (!zombie->init(zombieDescriptor))
	{
		delete zombie;
		return nullptr;
	}

	zombie->setCollisionMap(collisionMap);
	return zombie;
}
bool Zombie::init(const ZombieDescriptor& zombieDescriptor)
{
	if (!Character::init(zombieDescriptor))
		return false;

	
	m_sprite.setScale(0.4f, 0.4f);
	m_speed = zombieDescriptor.speed;
	m_spawnPosition = m_position;
	return true;
}

void Zombie::update(float deltaMilliseconds)
{
	float dt = deltaMilliseconds / 1000.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_direction.x = -1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_direction.x = 1.0f;
	}
	else
	{
		m_direction.x = .0f;
	}
	
	// Update final position
	// IMPORTANT NOTE!! We are using delta time to change the position according to the elapsed time so, it doesn't matter how many FPS (calls to update per second) we do, 
	// the sprite changes according to the elapsed time and not to the number of calls
	m_position.x += (m_direction.x * m_speed.x * dt);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_isOnGround)
	{
		m_velocity.y = -m_jumpForce;
		m_isOnGround = false;
	}
	
	gravity(deltaMilliseconds, m_gravity);

	if(m_position.y > m_deathY)
	{
		m_position = m_spawnPosition;
		m_velocity = { 0.f,0.f };
		m_isOnGround = false;
	}

	Character::update(deltaMilliseconds);
}

void Zombie::respawnAtStart()
{
	m_position = m_spawnPosition;
	m_velocity = { 0.f,0.f };
	m_isOnGround = false;
}

sf::FloatRect Zombie::getBounds() const
{
	sf::FloatRect b = m_sprite.getGlobalBounds();

	const float insetX = 24.f;
	const float insetY = 24.f;

	b.left += insetX;
	b.top += insetY;
	b.width -= insetX * 2.f;
	b.height -= insetY * 2.f;
	return b;
}


