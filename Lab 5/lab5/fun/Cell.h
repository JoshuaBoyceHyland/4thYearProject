#pragma once
#include <SFML/Graphics.hpp>
#include "Loader.h"
#include "Node.h"


enum class TraversalProperty { Walkable, Unwalkable, Job };

class Cell
{
	public:

		Cell( float t_width, float t_height, int t_row=-1, int t_column=-1, sf::Vector2f t_position = { -100, -100 });

		void draw(sf::RenderWindow& t_window);

		void outlineEnabled(bool t_enabled);

		void setPosition(sf::Vector2f t_position);

		void setTexture(Texture* t_texture);

		void setProperty(TraversalProperty t_property);

		void setColor(sf::Color t_color) { m_body.setFillColor(t_color); }

		void enableText(bool t_enabled) { m_textActive = t_enabled; }

		void debug(bool t_debug);

		void setText(std::string t_string) { m_text.setString(t_string); }

		bool isOccupied() { return m_occupied; };

		Node* getNode() { return &m_node; }

		Texture* getTexture() { return m_texture; };

		TraversalProperty getProperty() { return m_property; }
		sf::RectangleShape m_body;
	protected:

		void setUpText();

		int m_row;
		int m_column;
		Node m_node;

		bool m_textActive = true;

		sf::Font* m_font;

		sf::Text m_text;

		Texture* m_texture = nullptr;

		sf::Vector2f m_position;

		TraversalProperty m_property;

		bool m_occupied = false;
		
		std::map<TraversalProperty, std::string> m_cellPropertyString{ {TraversalProperty::Walkable, "Walkable"}, {TraversalProperty::Unwalkable, "Unwalkable"},{TraversalProperty::Job, "Job"} };
};

