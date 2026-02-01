#pragma once

#include <cstdint>
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>


namespace sf
{
	class RenderWindow;
}

class World;

class Game
{
	public:

		struct GameCreateInfo
		{
			std::string gameTitle;
			uint32_t screenWidth;
			uint32_t screenHeight;
			uint32_t frameRateLimit;
		};

		~Game();

		bool init(GameCreateInfo& createInfo);

		bool isRunning() const;

		void update(uint32_t deltaMilliseconds);
		void render();

	private:

		sf::Font m_font;
		sf::Text m_fpsText;
		sf::Text m_winText;
		sf::Clock m_winClock;
		sf::Text m_loseText;
		sf::Clock m_loseClock;

		sf::RenderWindow* m_window{ nullptr };
		World* m_world{ nullptr };
		bool m_startedLoseTimer{ false };
		bool m_startedWinTimer{ false };
};