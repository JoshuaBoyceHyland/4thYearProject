#pragma once
#include "Cell.h"

class Grid
{
	public:

		Grid();

		Grid(int t_rows, int t_columns, float t_width, float t_height, sf::Vector2f t_startPosition);
		
		void draw(sf::RenderWindow& t_window);

		void changeToWalkable(sf::Vector2f t_mouseCLick);

		void setForGamePlay();

		void placePiece(sf::Vector2f t_mouseCLick, std::vector<Texture*> t_textures, TraversalProperty t_property);

		std::vector<std::vector<Cell>> m_cells;

	private:

		float m_cellHeight;
		float m_cellWidth;

		int MAX_ROWS;
		int MAX_COLUMS;

		
};

