#pragma once

#include <Gameplay/GameObject.h>
#include <SFML/Graphics/Sprite.hpp>
#include <tmxlite/Map.hpp>
#include <Render/SFMLOrthogonalLayer.h>
#include <Core/CollisionMap.h>

class Character : public GameObject
{
	public:

		struct CharacterDescriptor
		{
			sf::Vector2f position;
			sf::Texture* texture{ nullptr };
			float tileWidth{ .0f };
			float tileHeight{ .0f };
		};

		~Character() override = default;

		bool init(const CharacterDescriptor& enemyDescriptor);

		void update(float deltaMilliseconds) override;
		void render(sf::RenderWindow& window) override;

		void gravity(float daltaMilliseconds, float gravity);
		void setCollisionMap(CollisionMap* collisionMap);;
	protected:

		sf::Sprite m_sprite;
		float m_tileWidth{ .0f };
		float m_tileHeight{ .0f };

		sf::Vector2f m_velocity{ 0.f,0.f };
		bool m_isOnGround = false;

		CollisionMap* m_collisionMap{ nullptr };
};