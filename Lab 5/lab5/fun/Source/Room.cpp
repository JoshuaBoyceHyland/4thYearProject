#include "Room.h"

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

   m_grid.inactiveCellsDeletion();
}

Room::Room(Grid t_grid) : m_grid(t_grid )
{
}

bool Room::emplaceOnGrid(Grid* t_backgroundGrid, sf::Vector2f t_mosuePosition)
{

    Cell* placingCell = t_backgroundGrid->cellSelection(t_mosuePosition);
    int startingRow = placingCell->getNode()->m_row; // start row of where we are placing it 
    int endingRow = placingCell->getNode()->m_row + m_grid.m_cells.size(); //  end column of where we are placing it

    std::cout << "New: " << std::endl;

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
                t_backgroundGrid->m_cells[row][column].setColor(sf::Color::White);
                t_backgroundGrid->m_cells[row][column].setTexture(m_grid.m_cells[placedPieceRow][placedPieceColumn].getTexture());
                t_backgroundGrid->m_cells[row][column].setProperty(m_grid.m_cells[placedPieceRow][placedPieceColumn].getProperty());
            }

            
        }
    }


    return false;
}

void Room::setPosition(sf::Vector2f t_mosuePosition)
{
    float startX = t_mosuePosition.x;
    
    for (int row = 0; row < m_grid.m_cells.size(); row++)
    {
        float xAxisIncrement = m_grid.m_cells[0][0].m_body.getSize().x;
        float yAxisIncrement = m_grid.m_cells[0][0].m_body.getSize().y;

        for (int column = 0; column < m_grid.m_cells[row].size(); column++)
        {
            m_grid.m_cells[row][column].setPosition(t_mosuePosition);

            t_mosuePosition.x += xAxisIncrement;
        }
        t_mosuePosition.x = startX;
        t_mosuePosition.y += yAxisIncrement;

    }
}



void Room::draw(sf::RenderWindow& t_window)
{
    m_grid.draw(t_window);
}
