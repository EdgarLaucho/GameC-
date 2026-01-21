#pragma once

#include <Gameplay/Enemy.h>


class Zombie : public Enemy
{
	public:

		struct ZombieDescriptor : EnemyDescriptor
		{
			sf::Vector2f speed{ .0f, .0f };
		};

		bool init(const ZombieDescriptor& enemyDescriptor);

		void update(float deltaMilliseconds) override;


	private:
		
		sf::Vector2f m_direction{ .0f, .0f };
		sf::Vector2f m_speed{ .0f, .0f };

		float m_gravity{ 0.0015f };
		float m_groundY{ 400.f };
		float m_jumpForce{ 0.40f };
		sf::Vector2f m_spawnPosition;
		float m_deathY{ 2000.f };

};