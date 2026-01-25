#pragma once

#include <Gameplay/Character.h>


class Zombie : public Character
{
	public:

		struct ZombieDescriptor : CharacterDescriptor
		{
			sf::Vector2f speed{ .0f, .0f };
		};

		bool init(const ZombieDescriptor& enemyDescriptor);
		static Zombie* createZombie(const sf::Vector2f& postion, CollisionMap* collisionMap);
		void update(float deltaMilliseconds) override;


	private:
		
		sf::Vector2f m_direction{ .0f, .0f };
		sf::Vector2f m_speed{ .0f, .0f };

		float m_gravity{ 2000.f };
		float m_groundY{ 400.f };
		float m_jumpForce{ 650.f };
		sf::Vector2f m_spawnPosition;
		float m_deathY{ 2000.f };

};