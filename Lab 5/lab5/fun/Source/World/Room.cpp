#include "World/Room.h"

Room::Room() :
    m_grid( 10, 10, 100, 100, {- (10 * 100), -(10 * 100) })
{
   
    TileLibrary* library = TileLibrary::getInstance();
    const int row = 0;
    const int column = 1;
    const int type = 2;
    const int texture = 3;
    std::vector<std::vector<int>> lines = FileReading::readFile("map.txt");

    for (std::vector<int> line : lines)
    {
        Tile* loadedTile = library->getTile(TraversalProperty(line[type]), line[texture]);

        m_grid.m_cells[line[row]][line[column]].setColor(sf::Color::White);
        m_grid.m_cells[line[row]][line[column]].setTexture(loadedTile->m_textures[0]);
        m_grid.m_cells[line[row]][line[column]].setProperty((*loadedTile).m_property);
    }

   m_grid.cullCells();
}

Room::Room(Grid t_grid) : m_grid(t_grid )
{
   //m_grid.cullCells();
}

void Room::projectOnGrid(Grid* t_backgroundGrid, sf::Vector2f t_mosuePosition)
{
    cleanUpProjection();

    Cell* placingCell = t_backgroundGrid->cellSelection(t_mosuePosition);

    if (placingCell == nullptr) { return; }

    int startingRow = placingCell->getNode()->m_row; // start row of where we are placing it 
    int endingRow = placingCell->getNode()->m_row + m_grid.m_cells.size(); //  end column of where we are placing it


    if (startingRow < 0 || startingRow >t_backgroundGrid->m_cells.size())
    {
        return;
    }

    if (endingRow < 0 || endingRow >t_backgroundGrid->m_cells.size())
    {
        return;
    }
    for (int row = startingRow; row < endingRow; row++)
    {
        int placedPieceRow = row - startingRow;

        int startingColumn = placingCell->getNode()->m_column;
        int endingColumn = placingCell->getNode()->m_column + m_grid.m_cells[placedPieceRow].size();

        for (int column = startingColumn; column < endingColumn; column++)
        {

            int placedPieceColumn = column - startingColumn;

            if (m_grid.m_cells[placedPieceRow][placedPieceColumn].getTexture() != nullptr)
            {
                t_backgroundGrid->m_cells[row][column].project(m_grid.m_cells[placedPieceRow][placedPieceColumn].getTexture());
                projectedOn.push(&t_backgroundGrid->m_cells[row][column]);
            }



        }
    }


}

void Room::cleanUpProjection()
{
    while (!projectedOn.empty())
    {
        projectedOn.front()->resetTexture();
        projectedOn.pop();
    }
}

bool Room::emplaceOnGrid(Grid* t_backgroundGrid, sf::Vector2f t_mosuePosition)
{

    Cell* placingCell = t_backgroundGrid->cellSelection(t_mosuePosition);

    if (placingCell == nullptr) { return false; }

    int startingRow = placingCell->getNode()->m_row; // start row of where we are placing it 
    int endingRow = placingCell->getNode()->m_row + m_grid.m_cells.size(); //  end column of where we are placing it
 

    for (int row = startingRow; row < endingRow; row++)
    {
        int placedPieceRow = row - startingRow;

        int startingColumn = placingCell->getNode()->m_column;
        int endingColumn = placingCell->getNode()->m_column + m_grid.m_cells[placedPieceRow].size();

        cellsOccupied.push_back(std::vector<Cell*>());

        for (int column = startingColumn; column < endingColumn; column++)
        {
            
            int placedPieceColumn = column - startingColumn;
            
            cellsOccupied[cellsOccupied.size() - 1].push_back(&t_backgroundGrid->m_cells[row][column]);
            
            if (m_grid.m_cells[placedPieceRow][placedPieceColumn].getTexture() != nullptr)
            {
                t_backgroundGrid->m_cells[row][column].setColor(sf::Color::White);
                t_backgroundGrid->m_cells[row][column].setTexture(m_grid.m_cells[placedPieceRow][placedPieceColumn].getTexture());
                t_backgroundGrid->m_cells[row][column].setProperty(m_grid.m_cells[placedPieceRow][placedPieceColumn].getProperty());
            }
            else
            {
                t_backgroundGrid->m_cells[row][column].setColor(sf::Color::White);
                t_backgroundGrid->m_cells[row][column].setProperty(m_grid.m_cells[placedPieceRow][placedPieceColumn].getProperty());
                
                
            }

            
        }
    }


    return false;
}

void Room::setPosition(sf::Vector2f t_mosuePosition)
{
    m_grid.setPosition(t_mosuePosition);
}



void Room::draw(sf::RenderWindow& t_window)
{
    m_grid.draw(t_window);
}

void Room::scaleDown(float t_scaleValue)
{
    for (int row = 0; row < m_grid.m_cells.size(); row++)
    {
        for (int column = 0; column < m_grid.m_cells.size(); column++)
        {
            m_grid.m_cells[row][column].m_body.setSize({ m_grid.m_cells[row][column].m_body.getSize().x * t_scaleValue, m_grid.m_cells[row][column].m_body.getSize().y * t_scaleValue });
        }
    }
}

void Room::rotate()
{
    m_grid.rotate();
}

void Room::setWalkable()
{
    for (int row = 0; row < m_grid.m_cells.size(); row++)
    {
        for (int column = 0; column < m_grid.m_cells[row].size(); column++)
        {
            m_grid.m_cells[row][column].setProperty(TraversalProperty::Walkable);
        }
    }
}

Cell* Room::getCenterCell()
{


    return cellsOccupied[cellsOccupied.size() / 2][cellsOccupied.size() / 2];
}

Grid Room::getGrid()
{
    return m_grid;
}

void Room::setColourOfOccupiedCells(sf::Color t_color)
{

    for (int row = 0; row < cellsOccupied.size(); row++)
    {
        for (int column = 0; column < cellsOccupied[row].size(); column++)
        {
            cellsOccupied[row][column]->m_body.setFillColor(t_color);
        }
    }
}

Cell* Room::getClosestCellTo(sf::Vector2f t_position)
{
    int closestRow = 0;
    int closestColum = 0;
    float closestDistance = VectorMath::vectorLength(t_position, cellsOccupied[0][0]->m_body.getPosition());
    for (int row = 0; row < cellsOccupied.size(); row++)
    {
        for (int column = 0; column < cellsOccupied[row].size(); column++)
        {
            float distance = VectorMath::vectorLength(t_position, cellsOccupied[row][column]->m_body.getPosition());

            if (distance < closestDistance)
            {
                closestDistance = distance;

                closestRow = row;
                closestColum = column;
            }
        }
    }

    return cellsOccupied[closestRow][closestColum];
}
