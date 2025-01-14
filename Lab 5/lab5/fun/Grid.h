#pragma once
#include "Cell.h"

class Grid
{
	public:
		Grid(int t_rows, int t_columns, float t_width, float t_height, sf::Vector2f t_startPosition);
		void draw(sf::RenderWindow& t_window);
<<<<<<< Updated upstream
=======

		void changeToWalkable(sf::Vector2f t_mouseCLick);

		void placePiece(sf::Vector2f t_mouseCLick, std::vector<sf::Texture*> t_textures, TraversalProperty t_property);

		std::vector<std::vector<Cell>> m_cells;
>>>>>>> Stashed changes
	private:

		float m_cellHeight;
		float m_cellWidth;

		int MAX_ROWS;
		int MAX_COLUMS;

		std::vector<std::vector<Cell>> m_cells;
};

