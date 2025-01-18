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
			if (m_cells[row][column].getTexture() == nullptr)
			{
				m_cells[row][column].setColor(sf::Color::Black);
				m_cells[row][column].outlineEnabled(false);
				m_cells[row][column].enableText(false);
			}
			
		}
	}


	setUpNeighbours();
}

void Grid::placePiece(sf::Vector2f t_mouseCLick, std::vector<Texture*> t_textures, TraversalProperty t_property)
{
	// ensureing the mouse click is valid
	if (t_mouseCLick.y < 0) { return; }
	if (t_mouseCLick.x < 0) { return; }

	int row = t_mouseCLick.y / m_cellHeight;
	int column = t_mouseCLick.x / m_cellWidth;

	// checking the row and column is in the bounds
	if (row < 0 || row >= MAX_ROWS) { return; }
	if (column  < 0 || column >= MAX_COLUMS) { return; }

	std::cout << row << " " << column << std::endl;
	m_cells[row][column].setColor(sf::Color::White);
	m_cells[row][column].setTexture(t_textures[0]);
	m_cells[row][column].setProperty(t_property);

}

void Grid::highlightNeighbours(sf::Vector2f t_mouseCLick)
{
	if (t_mouseCLick.y < 0) { return; }
	if (t_mouseCLick.x < 0) { return; }

	int row = t_mouseCLick.y / m_cellHeight;
	int column = t_mouseCLick.x / m_cellWidth;

	// checking the row and column is in the bounds
	if (row < 0 || row >= MAX_ROWS) { return; }
	if (column < 0 || column >= MAX_COLUMS) { return; }


	std::vector<Cell*> neighbours = m_cells[row][column].getNeighbours();

	for (int i = 0; i < neighbours.size(); i++)
	{
		neighbours[i]->setColor(sf::Color::Green);
	}
}

void Grid::setGridCosts(sf::Vector2f t_mouseCLick)
{

	if (t_mouseCLick.y < 0) { return; }
	if (t_mouseCLick.x < 0) { return; }

	int row = t_mouseCLick.y / m_cellHeight;
	int column = t_mouseCLick.x / m_cellWidth;

	// checking the row and column is in the bounds
	if (row < 0 || row >= MAX_ROWS) { return; }
	if (column < 0 || column >= MAX_COLUMS) { return; }

	int cost = 0;
	
	m_cells[row][column].setCost(cost);


	std::vector<Cell*> currentNeightbours;

	for (int i = 0; i < m_cells[row][column].getNeighbours().size(); i++)
	{
		if (!m_cells[row][column].getNeighbours()[i]->isMarked())
		{
			currentNeightbours.push_back(m_cells[row][column].getNeighbours()[i]);
		}
	}

	std::vector<Cell*> nextNeighbours = currentNeightbours;// just for set up

	while (!nextNeighbours.empty())
	{
		cost++;

		nextNeighbours.clear();

		// collect next set of neighbours
		for (int i = 0; i < currentNeightbours.size(); i++)
		{

			// if marked or goal dont set cost
			if (!currentNeightbours[i]->isMarked() && currentNeightbours[i]->getCost() !=0)
			{
				currentNeightbours[i]->setCost(cost);
				currentNeightbours[i]->setMarked(true);
			}


			for (int k = 0; k < currentNeightbours[i]->getNeighbours().size(); k++)
			{
				if (!currentNeightbours[i]->getNeighbours()[k]->isMarked() && !currentNeightbours[i]->getNeighbours()[k]->isBeingChecked())
				{
					currentNeightbours[i]->getNeighbours()[k]->setBeingChecked(true);
					nextNeighbours.push_back(currentNeightbours[i]->getNeighbours()[k]);
				}

			}

		}

		currentNeightbours.clear();
		currentNeightbours = nextNeighbours;

	}


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
						m_cells[row][column].setNeighbours(&m_cells[possibleRowNeighbour][possibleColNeighbour]);
					}
					
				}
			}
			
			

		}
	}
}
