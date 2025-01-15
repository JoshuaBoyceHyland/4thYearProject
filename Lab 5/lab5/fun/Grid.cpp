#include "Grid.h"

Grid::Grid()
{
}

Grid::Grid(int t_rows, int t_columns, float t_width, float t_height, sf::Vector2f t_startPosition) :
	MAX_ROWS( t_rows ), MAX_COLUMS( t_columns ), m_cellWidth( t_width ), m_cellHeight( t_height)
{
	float xStart = t_startPosition.x;
	for (int row = 0; row < MAX_ROWS; row++)
	{
		m_cells.push_back(std::vector<Cell>());
		for (int column = 0; column < MAX_COLUMS; column++)
		{
			m_cells[row].push_back({ m_cellHeight, m_cellWidth, t_startPosition });
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


void Grid::changeToWalkable(sf::Vector2f t_mouseCLick)
{
	// ensureing the mouse click is valid
	if (t_mouseCLick.y < 0 ) { return; }
	if (t_mouseCLick.x  < 0 ) { return; }

	int row = t_mouseCLick.y / m_cellHeight;
	int column = t_mouseCLick.x / m_cellWidth;

	// checking the row and column is in the bounds
	if (row < 0 || row > MAX_ROWS) { return; }
	if (column  < 0 || column > MAX_COLUMS) { return; }

	m_cells[row][column].setProperty(TraversalProperty::Walkable);
	
}

void Grid::setForGamePlay()
{
	for (int row = 0; row < m_cells.size(); row++)
	{
		for (int column = 0; column < m_cells[row].size(); column++)
		{
			m_cells[row][column].setColor(sf::Color::White);
		}
	}
}

void Grid::placePiece(sf::Vector2f t_mouseCLick, std::vector<Texture*> t_textures, TraversalProperty t_property)
{
	// ensureing the mouse click is valid
	if (t_mouseCLick.y < 0) { return; }
	if (t_mouseCLick.x < 0) { return; }

	int row = t_mouseCLick.y / m_cellHeight;
	int column = t_mouseCLick.x / m_cellWidth;

	// checking the row and column is in the bounds
	if (row < 0 || row > MAX_ROWS) { return; }
	if (column  < 0 || column > MAX_COLUMS) { return; }

	m_cells[row][column].setColor(sf::Color::White);
	m_cells[row][column].setTexture((*t_textures[0]));
	m_cells[row][column].setProperty(t_property);

}
