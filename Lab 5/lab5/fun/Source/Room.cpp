#include "Room.h"

Room::Room() :
    m_grid( 10, 10, 100, 100, {- (10 * 100), -(10 * 100) })
{
   
    std::ifstream file;
    file.open("map.txt");

    TileLibrary* library = TileLibrary::getInstance();
    int column, row, type, texture;
    std::string currentLine;

    while (std::getline(file, currentLine))
    {
        std::istringstream stringStream(currentLine);

        stringStream >> row >> column >> type >> texture;

        Tile* loadedTile = library->getTile(TraversalProperty(type), texture);

        m_grid.m_cells[row][column].setColor(sf::Color::White);
        m_grid.m_cells[row][column].setTexture(loadedTile->m_textures[0]);
        m_grid.m_cells[row][column].setProperty((*loadedTile).m_property);

        

    }

    file.close();
}

void Room::draw(sf::RenderWindow& t_window)
{
    m_grid.draw(t_window);
}
