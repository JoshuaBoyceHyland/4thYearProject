#pragma once
#include "Cell.h"
#include "Utility/Texture.h"
#include "EditorItem.h"
class Tile : public EditorItem
{

	public:


		Tile(Texture* t_texture, float t_width, float t_height);

		Tile(Texture* t_texture, Texture* t_jobTexture, float t_width, float t_height);

		Tile(std::vector<Texture*> t_texture, float t_width, float t_height, int t_rows, int t_colums);

		void draw(sf::RenderWindow& t_window);

		void setPosition(sf::Vector2f t_position);

		std::vector<Texture*> m_textures;

		std::vector<Cell> m_cells;

		TraversalProperty m_property;
		
		

};

