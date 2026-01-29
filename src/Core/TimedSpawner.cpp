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
	m_nextSpawnPoint = 0;
}

void TimedSpawner::update(float  deltaMs, SpawnPool& pool)
{
	const float deltaSeconds = deltaMs / 1000.f;
	
	for (auto it = m_activeObjects.begin(); it != m_activeObjects.end();)
	{
		GameObject* obj = it->first;
		if (!obj || !obj->isActive())
		{
			it = m_activeObjects.erase(it);
			continue;
		}
		it->second += deltaSeconds;

		if (it->second <0.f)
		{
			obj->setActive(false);
			it = m_activeObjects.erase(it);
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

	m_timer += deltaSeconds;

	if (m_timer < m_interval)
	{
		return;
	}
	m_timer = 0.f;

	if (pool.activeCount() >= m_maxAlive)
	{
		return;
	}

	const sf::Vector2f& spawnPos = m_spawnPoints[m_nextSpawnPoint];
	m_nextSpawnPoint = (m_nextSpawnPoint + 1) % m_spawnPoints.size();

	GameObject* newObj = pool.acquire(spawnPos);
	if (newObj) 
	{
		m_activeObjects[newObj] = m_lifeTime;
	}

}