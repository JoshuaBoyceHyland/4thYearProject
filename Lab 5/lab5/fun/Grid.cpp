#include "Grid.h"

Grid::Grid(int t_rows, int t_columns, float t_width, float t_height, sf::Vector2f t_startPosition) :
	MAX_ROWS( t_rows ), MAX_COLUMS( t_columns ), m_cellWidth( t_width ), m_cellHeight( t_height)
{
	float xStart = t_startPosition.x;
	for (int row = 0; row < MAX_ROWS; row++)
	{
		m_cells.push_back(std::vector<Cell>());
		for (int column = 0; column < MAX_COLUMS; column++)
		{
			m_cells[row].push_back({ t_startPosition, m_cellHeight, m_cellWidth });
			t_startPosition.x += m_cellWidth;
		}
		t_startPosition.x = xStart;
		t_startPosition.y += m_cellHeight;
	}
}

void Grid::draw(sf::RenderWindow& t_window)
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int column = 0; column < MAX_COLUMS; column++)
		{
			m_cells[row][column].draw(t_window);
		}
	}
}
