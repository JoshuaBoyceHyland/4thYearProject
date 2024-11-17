#pragma once
#include <SFML/Graphics.hpp>

class UI
{
	public:
		virtual void draw(sf::RenderWindow& t_window) = 0;
		virtual void checkForInteraction(sf::Vector2f t_mousePosition) = 0;
	protected:

		sf::Color m_lightBlue = sf::Color(209, 255, 255);
		sf::Color m_darkBlue = sf::Color(14, 34, 99);
		const float SCALING = 100;
};

