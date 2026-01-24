#include <Gameplay/Zombie.h>
#include <SFML/Window/Keyboard.hpp>

bool Zombie::init(const ZombieDescriptor& zombieDescriptor)
{
	if (!Character::init(zombieDescriptor))
		return false;

	
	m_sprite.setScale(0.3f, 0.3f);
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
