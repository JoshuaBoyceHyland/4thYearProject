#pragma once
#include <SFML/Graphics.hpp>
#include "Loader.h"

enum class TraversalProperty { Walkable, Unwalkable, Job };

class Cell
{
	public:

		Cell(float t_width, float t_height, sf::Vector2f t_position = { -100, -100 });

		void draw(sf::RenderWindow& t_window);

		void outlineEnabled(bool t_enabled);

		void setPosition(sf::Vector2f t_position);

		void setTexture(Texture* t_texture);

		void setProperty(TraversalProperty t_property);

		void setColor(sf::Color t_color) { m_body.setFillColor(t_color); }

		void enableText(bool t_enabled) { m_textActive = t_enabled; }
	
		TraversalProperty getProperty() { return m_property; }
		
		Texture* getTexture() { return m_texture; };

		
	protected:

		void setUpText();

		bool m_textActive = true;

		sf::Font* m_font;

		sf::Text m_text;

		sf::RectangleShape m_body;

		Texture* m_texture = nullptr;

		sf::Vector2f m_position;

		TraversalProperty m_property;

		std::map<TraversalProperty, std::string> m_cellPropertyString{ {TraversalProperty::Walkable, "Walkable"}, {TraversalProperty::Unwalkable, "Unwalkable"},{TraversalProperty::Job, "Job"} };
};

