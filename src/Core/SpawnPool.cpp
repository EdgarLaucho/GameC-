#include <Core/SpawnPool.h>
#include <Gameplay/GameObject.h>
#include <SFML/Graphics/RenderWindow.hpp>

SpawnPool::SpawnPool() = default;

SpawnPool::SpawnPool(CreateFn createFn, ResetFn resetFn) : m_createFn(std::move(createFn)), m_resetFn(std::move(resetFn)){}

GameObject* SpawnPool::acquire(const sf::Vector2f& position)
{
	for (auto& obj : m_objects)
	{
		if (!obj->isActive())
		{
			m_resetFn(*obj, position);
			obj->setActive(true);
			return obj.get();
		}
	}
	auto newObj = m_createFn(position);
	if (!newObj) return nullptr;
	
	newObj->setActive(true);
	m_objects.emplace_back(std::move(newObj));
	return m_objects.back().get();
}

void SpawnPool::updateAll(float deltaMs)
{
	for (auto& obj : m_objects)
	{
		if (obj->isActive())
		{
			obj->update(deltaMs);
		}
	}
}

void SpawnPool::renderAll(sf::RenderWindow& window)
{
	for (auto& obj : m_objects)
	{
		if (obj->isActive())
		{
			obj->render(window);
		}
	}
}

int SpawnPool::activeCount() const
{
	int count = 0;
	for (auto& obj : m_objects)
	{
		if (obj->isActive())
		{
			++count;
		}
	}
	return count;
}
void SpawnPool::deactivateAll()
{
	for (auto& obj : m_objects)
	{
		obj->setActive(false);
	}
}