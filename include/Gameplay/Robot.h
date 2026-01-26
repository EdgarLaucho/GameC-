#pragma once
#include <Gameplay/Character.h>

class CollisionMap;

class Robot : public Character
{
public:
	struct RobotDescriptor : CharacterDescriptor
	{
		float speed{ 0.f };
	};

	static Robot* createRobot(const sf::Vector2f& postion, CollisionMap* collisionMap);

	bool init(const RobotDescriptor& robotDescriptor);

	void respawn(const sf::Vector2f& position);
	void update(float deltaMilliseconds) override;
	void setCollisionMap(CollisionMap* map);


private:
	

	float m_speed{ 0.f };
	int m_direction{ 1 };
};