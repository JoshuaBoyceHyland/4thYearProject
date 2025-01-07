#pragma once
#include <SFML/Graphics.hpp>
#include "Loader.h"

enum class NPCProperty { Walkable, Unwalkable, Job };

class Cell
{
	public:

		Cell(sf::Vector2f t_position, float t_width, float t_height);
		
		void draw(sf::RenderWindow& t_window);

		void setPosition(sf::Vector2f t_position);

		void setTexture(sf::Texture* t_texture);

		void setProperty(NPCProperty t_property);

		void setColor(sf::Color t_color) { m_body.setFillColor(t_color); }
		
		
	protected:

		void setUpText();

		sf::Font* m_font;

		sf::Text m_text;

		sf::RectangleShape m_body;

		sf::Texture* m_texture;

		sf::Vector2f m_position;

		NPCProperty m_property;

		std::map<NPCProperty, std::string> m_cellPropertyString{ {NPCProperty::Walkable, "Walkable"}, {NPCProperty::Unwalkable, "Unwalkable"},{NPCProperty::Job, "Job"} };;
};

