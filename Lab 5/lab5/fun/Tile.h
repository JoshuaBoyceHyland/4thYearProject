#pragma once
#include "Cell.h"

class Tile
{

	public:
		Tile(sf::Texture* t_texture, float t_width, float t_height);

		Tile(std::vector<sf::Texture*> t_texture, float t_width, float t_height, int t_rows, int t_colums);

		void draw(sf::RenderWindow& t_window);

		void setPosition(sf::Vector2f t_position);

		std::vector<sf::Texture*> m_textures;

		std::vector<Cell> m_cells;

		TraversalProperty m_property;
		
		

};

