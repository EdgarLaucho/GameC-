#pragma once
#include <vector>
#include <random>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>

class SpawnPool;
class GameObject;

class TimedSpawner 
{
	public:
		void setEnabled(bool enabled);
		void SetIntervalRange(float minSeconds, float maxSeconds);
		void setMaxAlive(int maxAlive);
		void setLifetimeRange(float minSeconds, float maxSeconds);
		void setSpawnPoints(const std::vector<sf::Vector2f>& points);

		void update(float deltaMs, SpawnPool& pool);

	private:
		float randomRange(float minV, float maxV);

		bool m_enabled = true;
		float m_minInterval = 2.0f;
		float m_maxInterval = 2.0f;
		float m_minLifeTime = 10.0f;
		float m_maxLifeTime = 10.0f;

		float m_nextInterval = 2.0f;

		float m_spawnTimer = 0.f;
		int m_maxAlive = 3;

		std::vector<sf::Vector2f> m_spawnPoints;
		size_t m_nextSpawnIndex = 0;

		std::unordered_map<GameObject*, float> m_timeToLive; 

		std::mt19937 m_rng{ std::random_device{}() };

};
