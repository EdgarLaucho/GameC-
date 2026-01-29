#include <Core/TimedSpawner.h>
#include <Core/SpawnPool.h>
#include <Gameplay/GameObject.h>

void TimedSpawner::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

void TimedSpawner::SetInterval(float seconds)
{
	m_interval = seconds;
}

void TimedSpawner::setMaxAlive(int maxAlive)
{
	m_maxAlive = maxAlive;
}

void TimedSpawner::setLifetime(float seconds)
{
	m_lifeTime = seconds;
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

	if (m_spawnTimer < m_interval)
	{
		return;
	}
	m_spawnTimer = 0.f;

	if (pool.activeCount() >= m_maxAlive)
	{
		return;
	}

	const sf::Vector2f& spawnPos = m_spawnPoints[m_nextSpawnIndex];
	m_nextSpawnIndex = (m_nextSpawnIndex + 1) % m_spawnPoints.size();

	GameObject* newObj = pool.acquire(spawnPos);
	if (newObj) 
	{
		m_timeToLive[newObj] = m_lifeTime;
	}

}