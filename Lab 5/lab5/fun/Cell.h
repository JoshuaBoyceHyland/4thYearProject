#pragma once
#include <SFML/Graphics.hpp>

enum class Purpose { Walkable, Job, Wall };
class Cell
{
	public:
<<<<<<< Updated upstream
		Cell(sf::Vector2f t_position, float t_width, float t_height);

		void draw(sf::RenderWindow& t_window);
	private:
=======

		Cell(float t_width, float t_height, sf::Vector2f t_position = { -100, -100 });

		void draw(sf::RenderWindow& t_window);

		void setPosition(sf::Vector2f t_position);

		void setTexture(sf::Texture* t_texture);

		void setProperty(TraversalProperty t_property);

		void setColor(sf::Color t_color) { m_body.setFillColor(t_color); }
		
		TraversalProperty getProperty() { return m_property; }
		
	protected:

		void setUpText();

		sf::Font* m_font;

		sf::Text m_text;

>>>>>>> Stashed changes
		sf::RectangleShape m_body;
		sf::Vector2f m_position;

};

