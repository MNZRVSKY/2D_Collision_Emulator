#pragma once
#include <SFML/Graphics/Color.hpp>
namespace Constants
{
	const int WINDOW_MENU_WIDTH = 240;
	const int WINDOW_MENU_PADDING = 20;
	const int WINDOW_GAME_WIDTH = 640;
	const int WINDOW_WIDTH = WINDOW_GAME_WIDTH + WINDOW_MENU_WIDTH;
	const int WINDOW_HEIGHT = 480;

	const float PI = 3.14159265f;

	const float BULLET_RADIUS = 10.f;

	const int BLOCK_COUNT = 15;
	const float BLOCK_WIDTH = 43.f;
	const float BLOCK_HEIGHT = 26.f;

	const float MIN_ENGEL = 1.f;
	const float MAX_ENGEL = 360.f;

	const float MIN_SPEED = 1.f;
	const float MAX_SPEED = 10.f;

	const float MIN_DELAYTIME = 0.f;
	const float MAX_DELAYTIME = 10.f;

	const float MIN_LIFETIME = 20.f;
	const float MAX_LIFETIME = 100.f;

	const char WINDOW_LABEL[] = "Test task A4 Games";

	const char ANGEL_SLIDER_LABEL[] =	 "Angel";
	const char SPEED_SLIDER_LABEL[] =	 "Speed";
	const char DELAY_SLIDER_LABEL[] =	 "Delay";
	const char LIFETIME_SLIDER_LABEL[] = "Life time";
	const char BUTTON_RESET_LABEL[] =	 "Reset wall";

	const sf::Color BACKGROUND_COLOR =		sf::Color(193, 199, 189);
	const sf::Color MENU_BACKGROUND_COLOR = sf::Color(53, 56, 55);
	const sf::Color BULLET_COLOR =			sf::Color(0, 0, 0);
	const sf::Color BLOCK_COLOR_1 =			sf::Color(171, 73, 21);
	const sf::Color BLOCK_COLOR_2 =			sf::Color(217, 84, 13);
}