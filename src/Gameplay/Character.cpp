#include <Gameplay/Character.h>
#include <SFML/Graphics/RenderWindow.hpp>

bool Character::init(const CharacterDescriptor& enemyDescriptor)
{
	m_sprite.setTexture(*enemyDescriptor.texture);
	m_sprite.setPosition(enemyDescriptor.position);
	
	m_tileWidth = enemyDescriptor.tileWidth;
	m_tileHeight = enemyDescriptor.tileHeight;

	m_position = enemyDescriptor.position;
	m_velocity = sf::Vector2f(0.f, 0.f);
	m_isOnGround = false;
	
	return true;
}

void Character::setCollisionMap(CollisionMap* collisionMap)
{
	m_collisionMap = collisionMap;
}

void Character::gravity(float deltaMilliseconds, float gravity)
{
        float dt = deltaMilliseconds / 1000.f;
        m_velocity.y += gravity * dt;
        float newY = m_position.y + m_velocity.y * dt;

        if (m_collisionMap)
        {
            auto tileSize = m_collisionMap->getTileSize();

            float scaledWidth = m_tileWidth * m_sprite.getScale().x;
            float scaledHeight = m_tileHeight * m_sprite.getScale().y;

            // Punto inferior del zombie (los pies)
            float feetY = newY + scaledHeight;
            float centerX = m_position.x + scaledWidth * 0.5f;

            int tileX = static_cast<int>(centerX / tileSize.x);
            int tileY = static_cast<int>(feetY / tileSize.y);

            if (m_collisionMap->isSolid(tileX, tileY) && m_velocity.y > 0.f)
            {
                m_velocity.y = 0.f;
                m_isOnGround = true;

               
                newY = tileY * tileSize.y - scaledHeight;
            }
            else 
            {
				m_isOnGround = false;
            }
        }else
        {
            m_isOnGround = false;
        }

        m_position.y = newY;
    
}



void Character::update(float deltaMilliseconds)
{
	m_sprite.setPosition(m_position);
}

void Character::render(sf::RenderWindow& window)
{
	// Extend this mechanism to be able to support animations
	m_sprite.setTextureRect(sf::IntRect(0, 0, 
		static_cast<int>(m_tileWidth), static_cast<int>(m_tileHeight)));

	window.draw(m_sprite);
}