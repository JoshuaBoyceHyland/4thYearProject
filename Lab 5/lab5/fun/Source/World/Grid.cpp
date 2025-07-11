#include "World/Grid.h"

Grid::Grid()
{
}

Grid::Grid(int t_rows, int t_columns, float t_width, float t_height, sf::Vector2f t_startPosition) :
	MAX_ROWS( t_rows ), MAX_COLUMS( t_columns ), m_cellWidth( t_width ), m_cellHeight( t_height)
{
	m_tag = Player_Base;
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

	m_body.setPosition(m_cells[0][0].m_body.getPosition());
}

bool Grid::isInGrid(sf::Vector2f t_position)
{
	sf::Vector2f regressToOrgin = m_cells[0][0].m_body.getPosition();

	t_position -= regressToOrgin;

	int row = t_position.y / m_cellHeight;
	int column = t_position.x / m_cellWidth;

	// checking the row and column is in the bounds
	if (row < 0 || row >= m_cells.size()) { return false; }
	if (column < 0 || column >= m_cells[0].size()) { return false; }


	return true;
}

void Grid::draw(sf::RenderWindow& t_window)
{
	

	sf::View view = t_window.getView();

	// bounds of camera
	sf::FloatRect viewRender(view.getCenter().x - view.getSize().x / 2.0f, view.getCenter().y - view.getSize().y / 2.0f, view.getSize().x, view.getSize().y );

	sf::Vector2f gridStart = m_cells[0][0].m_body.getPosition() - (m_cells[0][0].m_body.getSize() / 2.0f);

	// Use the first cell position as the origin
	float xMin = viewRender.left - gridStart.x;
	float yMin = viewRender.top - gridStart.y;

	float xMax = xMin + viewRender.width;
	float yMax = yMin + viewRender.height;

	// see what cells are visible from camera
	int colStart = std::max(0, static_cast<int>( xMin / m_cellWidth) ) ;
	int colEnd = std::min((int)m_cells[0].size() - 1, static_cast<int>( xMax / m_cellWidth));

	int rowStart = std::max(0, static_cast<int>(yMin / m_cellHeight));
	int rowEnd = std::min((int)m_cells.size() - 1, static_cast<int>(yMax / m_cellHeight));

	for (int row = rowStart; row <= rowEnd; ++row)
	{
		for (int col = colStart; col <= colEnd; ++col)
		{
			m_cells[row][col].draw(t_window);
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
			m_cells[row][column].getNode()->clearNeighbours(); // if generated just clears previousl assigned neighbours which wouldnt be valid for game play
			if (m_cells[row][column].getTexture() == nullptr)
			{
				m_cells[row][column].setColor(sf::Color::Transparent);
				m_cells[row][column].outlineEnabled(false);
				m_cells[row][column].enableText(false);

				
			}
			if (m_cells[row][column].getProperty() == TraversalProperty::Walkable && m_cells[row][column].getTexture() != nullptr)
			{
				m_traversableCells.push_back(&m_cells[row][column]);
			}
			else if (m_cells[row][column].getProperty() == TraversalProperty::Unwalkable && m_cells[row][column].getTexture() != nullptr)
			{
				m_wallCells.push_back(&m_cells[row][column]);
			}
		}
	}
	
	setUpNeighbours(true);
}

void Grid::deletePiece(sf::Vector2f t_mouseCLick, TraversalProperty t_currentEditorSection)
{
	Cell* selectedCell = cellSelection(t_mouseCLick);

	if (t_currentEditorSection != TraversalProperty::Job)
	{
		
		if (selectedCell == nullptr) { return; }

		selectedCell->reset();
	}
	else
	{
		if (selectedCell->m_cellJob != nullptr)
		{
			delete selectedCell->m_cellJob;
			selectedCell->m_cellJob = nullptr;
		}
		

		
	}
}

void Grid::placePiece(sf::Vector2f t_mouseCLick,EditorItem* t_tile)
{
	Cell* selectedCell = cellSelection(t_mouseCLick);
	if (selectedCell == nullptr) { return; }


	Tile* possibleTIle = dynamic_cast<Tile*>(t_tile);

	if (possibleTIle != nullptr)
	{
		if (possibleTIle->m_textures[0] != nullptr)
		{
			selectedCell->setColor(sf::Color::White);
			selectedCell->setTexture(possibleTIle->m_textures[0]);
		}
		else
		{

			selectedCell->m_cellJob = new WorldItem(*possibleTIle->m_cells[0].m_cellJob);
			selectedCell->m_cellJob->setPosition(selectedCell->m_body.getPosition());


		}
		selectedCell->setProperty(possibleTIle->m_property);
	}
	else
	{
		if (selectedCell->getProperty() == TraversalProperty::Walkable)
		{
			WorldItem* worldItem = dynamic_cast<WorldItem*>(t_tile);
			selectedCell->m_cellJob = new WorldItem(*worldItem);
			selectedCell->m_cellJob->setPosition(selectedCell->m_body.getPosition());
		}


	}
	

	

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

Cell* Grid::cellSelection(sf::Vector2f t_position)
{

	sf::Vector2f gridStart = m_cells[0][0].m_body.getPosition() - (m_cells[0][0].m_body.getSize() / 2.0f);

	sf::Vector2f offsettedClick = t_position - gridStart;


	if (offsettedClick.y < 0) { return nullptr; }
	if (offsettedClick.x < 0) { return nullptr; }

	int row = offsettedClick.y / m_cellHeight;
	int column = offsettedClick.x / m_cellWidth;

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

void Grid::cullCells()
{


	//for (auto rowIt = m_cells.begin(); rowIt != m_cells.end(); )
	//{

	//	for (auto columnIt = (*rowIt).begin(); columnIt != (*rowIt).end();)
	//	{
	//		if ((*columnIt).getTexture() == nullptr)
	//		{
	//			columnIt = (*rowIt).erase(columnIt);
	//		}
	//		else
	//		{
	//			++columnIt;
	//		}
	//	}

	//	// if the row is now empty we can delete it
	//	if ((*rowIt).empty())
	//	{
	//		rowIt = m_cells.erase(rowIt);
	//	}
	//	else
	//	{
	//		++rowIt;
	//	}
	//}


	int lastOccupiedROw = 0;
	int lastOccupiedColumn = 0;


}

void Grid::cullEmptyCellsW(int from)
{
	for (auto rowIt = m_cells.begin() ; rowIt != m_cells.end(); )
	{

		for (auto columnIt = (*rowIt).begin() + from + 1; columnIt != (*rowIt).end();)
		{
			columnIt = (*rowIt).erase(columnIt);
		}

		// if the row is now empty we can delete it
		if ((*rowIt).empty())
		{
			rowIt = m_cells.erase(rowIt);
		}
		else
		{
			++rowIt;
		}
	}
}

void Grid::cullEmptyCellsH(int from)
{

	for (auto rowIt = m_cells.begin() + from + 1; rowIt != m_cells.end(); )
	{

		for (auto columnIt = (*rowIt).begin(); columnIt != (*rowIt).end();)
		{
			columnIt = (*rowIt).erase(columnIt);
		}

		// if the row is now empty we can delete it
		if ((*rowIt).empty())
		{
			rowIt = m_cells.erase(rowIt);
		}
		else
		{
			++rowIt;
		}
	}
}

void Grid::setPosition(sf::Vector2f t_position)
{
	float offsetX = 0;
	float origin = m_cells[0][0].m_body.getPosition().x;
	float startX = t_position.x;
	float xAxisIncrement = 0;
	float yAxisIncrement = 0;
	
	for (int row = 0; row < m_cells.size(); row++)
	{
		
		offsetX = origin - m_cells[row][0].m_body.getPosition().x;
		t_position.x = startX - offsetX;

		for (int column = 0; column < m_cells[row].size(); column++)
		{
			xAxisIncrement = m_cells[row][column].m_body.getSize().x * m_cells[row][column].m_body.getScale().x;
			yAxisIncrement = m_cells[row][column].m_body.getSize().y * m_cells[row][column].m_body.getScale().x;

			m_cells[row][column].setPosition(t_position);
		
			t_position.x += xAxisIncrement;
		}

		
		t_position.y += yAxisIncrement;

	}

	m_cellWidth = xAxisIncrement;
	m_cellHeight = yAxisIncrement;
}

void Grid::scale(float xScale, float yScale)
{

	// get first cell
	sf::Vector2f currentPosition = m_cells[0][0].m_body.getPosition();

	float startX = currentPosition.x - m_cellWidth / 2;
	float startY = currentPosition.y;
	float XIncrement = 0;
	float YIncrement = 0;
	
	for (int row = 0; row < m_cells.size(); row++)
	{
		for (int column = 0; column <m_cells[row].size(); column++)
		{
			startX = m_cells[row][0].m_body.getPosition().x;

			XIncrement = m_cells[row][column].m_body.getSize().x * xScale;
			YIncrement = m_cells[row][column].m_body.getSize().y* yScale;

			m_cells[row][column].m_body.scale({ xScale,yScale });
			m_cells[row][column].setPosition({ currentPosition });

			currentPosition.x += XIncrement;
		}
		
		currentPosition.x = startX;
		currentPosition.y += YIncrement;
		

	}
}

void Grid::rotate()
{
	
	std::vector<std::vector<Cell>> temp = m_cells;

	for (int row = 0; row < temp.size(); row++)
	{
		for (int col = 0; col < temp[row].size(); col++)
		{
			int rotatedIndex = temp.size() - row - 1;
	
			m_cells[col][rotatedIndex] = Cell(temp[row][col], false);
			m_cells[col][rotatedIndex].m_body.rotate(90.0f);
		}
	}
}


void Grid::setUpNeighbours(bool t_requiresWalkable)
{

	const int NUM_OF_NEIGHBOURS = 8;

	std::vector<int> rowNeighbour = {-1,  0,  1, -1, 1, -1, 0, 1};
	std::vector<int> colNeighbour = { -1, -1, -1,  0, 0,  1, 1, 1 };
	for (int row = 0; row < m_cells.size(); row++)
	{
		for (int column = 0; column < m_cells[row].size(); column++)
		{
			if (m_cells[row][column].isOccupied() || !t_requiresWalkable)
			{
				for (int i = 0; i < NUM_OF_NEIGHBOURS; i++)
				{

					int possibleRowNeighbour = row + rowNeighbour[i];
					int possibleColNeighbour = column + colNeighbour[i];

					if (possibleRowNeighbour < 0 || possibleRowNeighbour >= m_cells.size()) { continue; }
					if (possibleColNeighbour < 0 || possibleColNeighbour >= m_cells[row].size()) { continue; }

					
					if (m_cells[possibleRowNeighbour][possibleColNeighbour].getProperty() == TraversalProperty::Walkable || !t_requiresWalkable)
					{
						//std::cout << "Row: " << row << " Col: " << column << " RowN: " << possibleRowNeighbour << " ColN: " << possibleColNeighbour << std::endl;
						m_cells[row][column].getNode()->addNeighbour(m_cells[possibleRowNeighbour][possibleColNeighbour].getNode());
						m_cells[row][column].getNode()->addNeighbourDirection(Direction(i));
					}
					
				}
			}
			
			

		}
	}
}

Cell* Grid::getRandomTraverableCell()
{
	int randomCell = rand() % m_traversableCells.size();
	
	return m_traversableCells[randomCell];
}

void Grid::collisionWith(Tag t_tag)
{
}
