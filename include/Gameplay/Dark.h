#pragma once

#include <Gameplay/Enemy.h>

class CollisionMap;

class Dark : public Enemy
{
public:
	struct DarkDescriptor : EnemyDescriptor
	{
		float speed{ 0.f };
	};

	static Dark* create(const sf::Vector2f& postion, CollisionMap* collisionMap);

	bool init(const DarkDescriptor& darkDescriptor);

	void update(float deltaMilliseconds) override;
	void setCollisionMap(CollisionMap* map);


private:
	

	CollisionMap* m_collisionMap{ nullptr };
	float m_speed{ 0.f };
	int m_direction{ 1 };
};