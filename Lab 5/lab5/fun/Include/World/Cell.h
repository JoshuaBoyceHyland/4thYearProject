#pragma once
#include <SFML/Graphics.hpp>
#include "Librarys/Loader.h"
#include "World/Node.h"
#include "WorldItems/WorldITem.h"
#include <unordered_set>
#include "GameObject.h"

enum class TraversalProperty { Walkable, Unwalkable, Job };

class Cell
{
	public:

		Cell( float t_width, float t_height, int t_row=-1, int t_column=-1, sf::Vector2f t_position = { -100, -100 });

		Cell(const Cell& t_other, bool t_copyPosition);

		void reset();

		void draw(sf::RenderWindow& t_window);

		void outlineEnabled(bool t_enabled);

		void setPosition(sf::Vector2f t_position);

		void setTexture(Texture* t_texture);

		void setProperty(TraversalProperty t_property);

		void addToGameObjects(GameObject* t_gameObject) { /*m_body.setFillColor(sf::Color::Green);*/ m_gameObjects.insert(t_gameObject); };

		void removeGameObject(GameObject* t_gameObject) { /*m_body.setFillColor(sf::Color::White);*/ m_gameObjects.erase(t_gameObject); };

		void setColor(sf::Color t_color) { m_body.setFillColor(t_color); }

		void project(Texture* t_texture);

		void project(WorldItem* t_job);

		void resetTexture();

		void enableText(bool t_enabled) { m_textActive = t_enabled; }

		void debug(bool t_debug);

		void setText(std::string t_string) { m_text.setString(t_string); }

		bool isOccupied() { return m_occupied; };

		Node* getNode() { return &m_node; }

		Texture* getTexture() { return m_texture; };

		TraversalProperty getProperty() { return m_property; }

		std::unordered_set<GameObject*> getGameObjects() { return m_gameObjects; };

		sf::RectangleShape m_body;

		WorldItem* m_cellJob = nullptr;
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


		std::unordered_set<GameObject*> m_gameObjects;

		std::map<TraversalProperty, std::string> m_cellPropertyString{ {TraversalProperty::Walkable, "Walkable"}, {TraversalProperty::Unwalkable, "Unwalkable"},{TraversalProperty::Job, "Job"} };
};

