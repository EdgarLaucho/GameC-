#include <Core/TimedSpawner.h>
#include <Core/SpawnPool.h>
#include <Gameplay/GameObject.h>
#include <cmath>
#include <algorithm>


void TimedSpawner::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

void TimedSpawner::SetIntervalRange(float minSeconds, float maxSeconds)
{
	m_minInterval = minSeconds;
	m_maxInterval = maxSeconds;
	m_nextInterval = randomRange(m_minInterval,m_maxInterval);
}

void TimedSpawner::setMaxAlive(int maxAlive)
{
	m_maxAlive = maxAlive;
}

void TimedSpawner::setLifetimeRange(float minSeconds, float maxSeconds)
{
	m_minLifeTime = minSeconds;
	m_maxLifeTime = maxSeconds;
}

float TimedSpawner::randomRange(float minV, float maxV)
{
	if(!std::isfinite(minV) || !std::isfinite(maxV))
	{
		return 0.f;
	}
	if (maxV < minV)
	{
		std::swap(minV, maxV);
	}
	if (minV == maxV)
	{
		return minV;
	}
	std::uniform_real_distribution<float> dist(minV, maxV);
	return dist(m_rng);
}

void TimedSpawner::setSpawnPoints(const std::vector<sf::Vector2f>& points)
{
	m_spawnPoints = points;
	m_nextSpawnIndex = 0;
}

void TimedSpawner::update(float  deltaMs, SpawnPool& pool)
{
	const float deltaSeconds = deltaMs / 1000.f;
	
	for (auto it = m_timeToLive.begin(); it != m_timeToLive.end();)
	{
		GameObject* obj = it->first;
		if (!obj || !obj->isActive())
		{
			it = m_timeToLive.erase(it);
			continue;
		}
		it->second -= deltaSeconds;

		if (it->second <0.f)
		{
			obj->setActive(false);
			it = m_timeToLive.erase(it);
			continue;
		}
		++it;
		
	}
	if (!m_enabled)
	{
		return;
	}

	if (m_spawnPoints.empty())
	{
		return;
	}

	m_spawnTimer += deltaSeconds;

	if (m_spawnTimer < m_nextInterval)
	{
		return;
	}
	m_spawnTimer = 0.f;

	m_nextInterval = randomRange(m_minInterval, m_maxInterval);

	if (pool.activeCount() >= m_maxAlive)
	{
		return;
	}

	const sf::Vector2f& spawnPos = m_spawnPoints[m_nextSpawnIndex];
	m_nextSpawnIndex = (m_nextSpawnIndex + 1) % m_spawnPoints.size();

	GameObject* newObj = pool.acquire(spawnPos);
	if (newObj) 
	{
		float ttl = randomRange(m_minLifeTime, m_maxLifeTime);
		if (ttl <= 0.f)
		{
			ttl = 0.f;
		}

		m_timeToLive[newObj] = ttl;
	}

}