#include <Gameplay/Character.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>


bool Character::init(const CharacterDescriptor& characterDescriptor)
{
	if(!characterDescriptor.texture)
    {
        std::cerr << "Textura nula" << std::endl;
            return false;
    }
    m_tileWidth = characterDescriptor.tileWidth;
    m_tileHeight = characterDescriptor.tileHeight;
    m_sprite.setTexture(*characterDescriptor.texture);
	m_position = characterDescriptor.position;
	m_velocity = sf::Vector2f(0.f, 0.f);
	m_isOnGround = false;
	
	m_sprite.setTextureRect(sf::IntRect(0, 0, (int)m_tileWidth, (int)m_tileHeight));
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

            const sf::Vector2f s = m_sprite.getScale();
            const float absScaleX = std::abs(s.x);
            const float absScaleY = std::abs(s.y);
			float scaledWidth = m_tileWidth * absScaleX;
            float scaledHeight = m_tileHeight * absScaleY;

            
            float feetY = newY + scaledHeight+1;
            float margin = 15.f;
            float leftX = m_position.x + margin;
            float rightX = m_position.x + scaledWidth - margin;
            int tileY = static_cast<int>(feetY / tileSize.y);

            int tileLeftX = static_cast<int>(leftX / tileSize.x);
            int tileRightX = static_cast<int>(rightX / tileSize.x);

            bool groundLeft = m_collisionMap->isSolid(tileLeftX, tileY);
            bool groundRight = m_collisionMap->isSolid(tileRightX, tileY);

            if ((groundLeft || groundRight) && m_velocity.y > 0.f)
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

void Character::takeHit()
{
	if (dead) return;

	hitCount++;
    if (hitCount >= 5)
    {
        dead = true;
    }
}



void Character::update(float deltaMilliseconds)
{
    if (!m_active) return;
	m_sprite.setPosition(m_position);
}

void Character::render(sf::RenderWindow& window)
{
    if (!m_active) return;
	// Extend this mechanism to be able to support animations
	//m_sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(m_tileWidth), static_cast<int>(m_tileHeight)));

	window.draw(m_sprite);
}
