#include <cassert>
#include <Core/Game.h>
#include <Core/World.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

bool Game::init(GameCreateInfo& createInfo)
{
	assert(m_window == nullptr && m_world == nullptr && "Game is already initialized, we are about to leak memory");

	m_window = new sf::RenderWindow({ createInfo.screenWidth, createInfo.screenHeight }, createInfo.gameTitle);
	m_window->setFramerateLimit(createInfo.frameRateLimit);
	m_world = new World();
	const bool loadOk = m_world->load();

	if (!loadOk)
		return false;
	if (!m_font.loadFromFile("../Data/Fonts/ARIAL.TTF"))
	{
		return false;
	}
	m_winText.setFont(m_font);
	m_winText.setString("You Win!");
	m_winText.setCharacterSize(75);
	m_winText.setFillColor(sf::Color::White);
	sf::FloatRect bounds = m_winText.getLocalBounds();
	m_winText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	m_winText.setPosition(m_window->getSize().x / 2.f, m_window->getSize().y / 2.f);

	return true;
}

Game::~Game()
{
	// To-Do: make sure m_world is unloaded()

	delete m_world;
	delete m_window;
}

bool Game::isRunning() const 
{ 
	return m_window->isOpen(); 
}

void Game::update(uint32_t deltaMilliseconds)
{
	// Check if user closed the window
	for (auto event = sf::Event(); m_window->pollEvent(event);)
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
		}
	}

	// Update scene here
	m_world->update(deltaMilliseconds);
}

void Game::render()
{
	m_window->clear();

	m_world->render(*m_window);

	if (m_world->hasWon())
	{
		m_window->draw(m_winText);
	}

	m_window->display();
}