#include <Gameplay/Dark.h>
#include <core/AssetManager.h>
#include <core//CollisionMap.h>
#include <SFML/Graphics/Texture.hpp>

Dark* Dark::create(const sf::Vector2f& postion, CollisionMap* collisionMap)
{
	sf::Texture* darkTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/dark.png");

	Dark::DarkDescriptor darkDescriptor;
	darkDescriptor.texture = darkTexture;
	darkDescriptor.position = postion;
	darkDescriptor.speed = { 400.f };
	darkDescriptor.tileWidth = 32.f;
	darkDescriptor.tileHeight = 32.f;
	Dark* dark = new Dark();

	if (!dark->init(darkDescriptor)) 
	{
		delete dark;
		return nullptr;
	}

	dark->setCollisionMap(collisionMap);
	return dark;
}

bool Dark::init(const DarkDescriptor& darkDescriptor) 
{
	bool ok = Enemy::init(darkDescriptor);
	
	int spriteWidth = 32;
	int spriteHeight = 32;

	m_sprite.setScale(64.f / 32.f,64.f / 32.f);
	m_speed = darkDescriptor.speed;
	m_direction = 1;
	return ok;
}

void Dark::setCollisionMap(CollisionMap* collisionMap) 
{
	m_collisionMap = collisionMap;
}

void Dark::update(float deltaMilliseconds) 
{
	if (!m_collisionMap) return;

	// Calculamos el movimiento horizontal
	float move = m_direction * m_speed * deltaMilliseconds;
	sf::Vector2f newPos = m_position;
	newPos.x += move;

	// Convertimos la posición al tile del mapa
	int tileBelowLeftX = static_cast<int>(newPos.x / m_collisionMap->getTileSize().x);
	int tileBelowRightX = static_cast<int>((newPos.x + m_tileWidth) / m_collisionMap->getTileSize().x);
	int tileBelowY = static_cast<int>((newPos.y + m_tileHeight) / m_collisionMap->getTileSize().y);

	// Evitamos caer de precipicios
	bool leftSolid = m_collisionMap->isSolid(tileBelowLeftX, tileBelowY);
	bool rightSolid = m_collisionMap->isSolid(tileBelowRightX, tileBelowY);

	// Cambiamos de dirección si hay un bloque sólido delante o no hay suelo
	int tileFrontX = m_direction == 1 ? tileBelowRightX : tileBelowLeftX;
	if (!m_collisionMap->isSolid(tileFrontX, tileBelowY) || !leftSolid || !rightSolid)
		m_direction *= -1;

	// Actualizamos posición
	m_position.x += m_direction * m_speed * deltaMilliseconds;

	Enemy::update(deltaMilliseconds);
}
