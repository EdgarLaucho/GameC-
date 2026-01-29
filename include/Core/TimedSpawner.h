#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>

class SpawnPool;
class GameObject;

class TimedSpawner 
{
	public:
		void setEnabled(bool enabled);
		void SetInterval(float secods);
		void setMaxAlive(int maxAlive);
		void setLifetime(float seconds);
		void setSpawnPoints(const std::vector<sf::Vector2f>& points);

		void update(float deltaMs, SpawnPool& pool);
	private:
		bool m_enabled = true;
		float m_interval = 2.0f;
		float m_lifeTime = 10;
		float m_timer = 0.f;
		int m_maxAlive = 3;

		std::vector<sf::Vector2f> m_spawnPoints;
		size_t m_nextSpawnPoint = 0;

		std::unordered_map<GameObject*, float> m_activeObjects; 
};
