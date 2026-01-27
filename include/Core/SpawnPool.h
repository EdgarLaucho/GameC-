#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject;

class SpawnPool
{
	public:
		using CreateFn = std::function<std::unique_ptr<GameObject>(const sf::Vector2f&)>;
		using ResetFn = std::function<void(GameObject&, const sf::Vector2f&)>;

		SpawnPool();
		SpawnPool(CreateFn createFn, ResetFn resetFn);

		GameObject* acquire(const sf::Vector2f& position);
		void updateAll(float deltaMs);
		void renderAll(sf::RenderWindow& window);
		int activeCount() const;
		void deactivateAll();
	private:
		std::vector<std::unique_ptr<GameObject>> m_objects;
		CreateFn m_createFn;
		ResetFn m_resetFn;
};