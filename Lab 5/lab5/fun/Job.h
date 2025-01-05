#pragma once
#include <SFML/Graphics.hpp>
#include "Loader.h"
class Job
{
	public:
		Job(std::string t_name, sf::Vector2f t_position);

		void draw(sf::RenderWindow& t_window);

	private:
		sf::Vector2f m_position;
		sf::Vector2f m_workingPosition;
		std::string m_name;
		sf::Text m_text;
		sf::Font* m_font;
};

