#pragma once
#include <SFML/Graphics.hpp>

enum class Purpose { Walkable, Job, Wall };
class Cell
{
	public:
		Cell(sf::Vector2f t_position, float t_width, float t_height);

		void draw(sf::RenderWindow& t_window);
	private:
		sf::RectangleShape m_body;
		sf::Vector2f m_position;

};

