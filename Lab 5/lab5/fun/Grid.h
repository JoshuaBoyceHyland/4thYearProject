#pragma once
#include "Cell.h"

class Grid
{
	public:
		Grid(int t_rows, int t_columns, float t_width, float t_height, sf::Vector2f t_startPosition);
		void draw(sf::RenderWindow& t_window);
	private:
		float m_cellHeight;
		float m_cellWidth;

		int MAX_ROWS;
		int MAX_COLUMS;

		std::vector<std::vector<Cell>> m_cells;
};

