#include <Gameplay/Enemy.h>
#include <SFML/Graphics/RenderWindow.hpp>

bool Enemy::init(const EnemyDescriptor& enemyDescriptor)
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

void Enemy::setCollisionMap(CollisionMap* collisionMap)
{
	m_collisionMap = collisionMap;
}

void Enemy::gravity(float deltaMilliseconds, float gravity)
{
        m_velocity.y += gravity * deltaMilliseconds;
        float newY = m_position.y + m_velocity.y * deltaMilliseconds;

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

                // Alineamos al suelo correctamente
                newY = tileY * tileSize.y - scaledHeight;
            }
        }

        m_position.y = newY;
    
}



void Enemy::update(float deltaMilliseconds)
{
	m_sprite.setPosition(m_position);
}

void Enemy::render(sf::RenderWindow& window)
{
	// Extend this mechanism to be able to support animations
	m_sprite.setTextureRect(sf::IntRect(0, 0, 
		static_cast<int>(m_tileWidth), static_cast<int>(m_tileHeight)));

	window.draw(m_sprite);
}