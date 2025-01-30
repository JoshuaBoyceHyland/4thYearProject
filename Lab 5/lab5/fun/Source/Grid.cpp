#include "Grid.h"

Grid::Grid()
{
}

Grid::Grid(int t_rows, int t_columns, float t_width, float t_height, sf::Vector2f t_startPosition) :
	MAX_ROWS( t_rows ), MAX_COLUMS( t_columns ), m_cellWidth( t_width ), m_cellHeight( t_height)
{

	t_startPosition.x += t_width / 2;
	t_startPosition.y += t_height / 2;

	float xStart = t_startPosition.x ;
	for (int row = 0; row < MAX_ROWS; row++)
	{
		m_cells.push_back(std::vector<Cell>());
		for (int column = 0; column < MAX_COLUMS; column++)
		{
			m_cells[row].push_back({ m_cellHeight, m_cellWidth,row, column, t_startPosition });
			t_startPosition.x += m_cellWidth;
		}
		t_startPosition.x = xStart;
		t_startPosition.y += m_cellHeight;
	}

	
}

void Grid::draw(sf::RenderWindow& t_window)
{
	for (int row = 0; row < m_cells.size(); row++)
	{
		for (int column = 0; column < m_cells[row].size(); column++)
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
			if (m_cells[row][column].getTexture() == nullptr)
			{
				m_cells[row][column].setColor(sf::Color::Black);
				m_cells[row][column].outlineEnabled(false);
				m_cells[row][column].enableText(false);

				
			}
			if (m_cells[row][column].getProperty() == TraversalProperty::Walkable && m_cells[row][column].getTexture() != nullptr)
			{
				m_traversableCells.push_back(&m_cells[row][column]);
			}
		}
	}
	
	setUpNeighbours();
}

void Grid::placePiece(sf::Vector2f t_mouseCLick, std::vector<Texture*> t_textures, TraversalProperty t_property)
{
	Cell* selectedCell = cellSelection(t_mouseCLick);
	if (selectedCell == nullptr) { return; }



	selectedCell->setColor(sf::Color::White);
	selectedCell->setTexture(t_textures[0]);
	selectedCell->setProperty(t_property);

}

void Grid::highlightNeighbours(sf::Vector2f t_mouseCLick)
{
	Cell* selectedCell = cellSelection(t_mouseCLick);
	if (selectedCell == nullptr) { return; }


	std::vector<Node*> neighbours = selectedCell->getNode()->getNeighbours();

	for (int i = 0; i < neighbours.size(); i++)
	{
		m_cells[neighbours[i]->m_row][neighbours[i]->m_column].setColor(sf::Color::Green);
	}
}

Cell* Grid::cellSelection(sf::Vector2f t_mouseCLick)
{
	if (t_mouseCLick.y < 0) { return nullptr; }
	if (t_mouseCLick.x < 0) { return nullptr; }

	int row = t_mouseCLick.y / m_cellHeight;
	int column = t_mouseCLick.x / m_cellWidth;

	// checking the row and column is in the bounds
	if (row < 0 || row >= MAX_ROWS) { return nullptr; }
	if (column < 0 || column >= MAX_COLUMS) { return nullptr; }



	return &m_cells[row][column];
}

void Grid::resetGridCellForPathFinding(bool t_resetCosts, bool t_resetMarkings)
{

	for (int row = 0; row < m_cells.size(); row++)
	{
		for (int column = 0; column < m_cells[row].size(); column++)
		{

			if (t_resetCosts)
			{
				m_cells[row][column].getNode()->resetCosts();
			}
			
			if (t_resetMarkings)
			{
				m_cells[row][column].getNode()->resetMarkings();
			}
			
		}

	}
}

void Grid::pathFind(sf::Vector2f t_mouseCLick)
{

	//Cell* selectedCell = cellSelection(t_mouseCLick);


	//if (selectedCell == nullptr){return;}

	//// reset pathfing propertys fully
	//resetGridCellForPathFinding(true, true);


	//Search::breadhFirstGridCostAssignment(selectedCell->getNode(), selectedCell->getNode()->getPosition());

	//// only reset the markings
	//resetGridCellForPathFinding(false, true);

	//std::vector<Node*> path = Search::AStar(m_cells[6][18].getNode() );

	//for (int i = 0; i < path.size(); i++)
	//{
	//	m_cells[path[i]->m_row][path[i]->m_column].setColor(sf::Color::Green);
	//}

	//// debug
	//for (int row = 0; row < m_cells.size(); row++)
	//{
	//	for (int column = 0; column < m_cells[row].size(); column++)
	//	{
	//		
	//		m_cells[row][column].debug(true);
	//	}

	//}


	
}

void Grid::inactiveCellsDeletion()
{

	for (int row = 0; row < m_cells.size(); row++)
	{
		for (auto it = m_cells[row].begin(); it != m_cells[row].end();)
		{
			if ((*it).getTexture() == nullptr)
			{
				it = m_cells[row].erase(it);
			}
			else 
			{
				++it;
			}
		}
	}

	std::cout << "made it" << std::endl;
}

void Grid::setUpNeighbours()
{

	const int NUM_OF_NEIGHBOURS = 8;

	std::vector<int> rowNeighbour = {-1,  0,  1, -1, 1, -1, 0, 1};
	std::vector<int> colNeighbour = { -1, -1, -1,  0, 0,  1, 1, 1 };
	
	for (int row = 0; row < m_cells.size(); row++)
	{
		for (int column = 0; column < m_cells[row].size(); column++)
		{
			if (m_cells[row][column].isOccupied())
			{
				for (int i = 0; i < NUM_OF_NEIGHBOURS; i++)
				{

					int possibleRowNeighbour = row + rowNeighbour[i];
					int possibleColNeighbour = column + colNeighbour[i];

					if (possibleRowNeighbour < 0 || possibleRowNeighbour >= m_cells.size()) { continue; }
					if (possibleColNeighbour < 0 || possibleColNeighbour >= m_cells[row].size()) { continue; }

					
					if (m_cells[possibleRowNeighbour][possibleColNeighbour].getProperty() == TraversalProperty::Walkable)
					{
						std::cout << "Row: " << row << " Col: " << column << " RowN: " << possibleRowNeighbour << " ColN: " << possibleColNeighbour << std::endl;
						m_cells[row][column].getNode()->addNeighbour(m_cells[possibleRowNeighbour][possibleColNeighbour].getNode());
					}
					
				}
			}
			
			

		}
	}
}
