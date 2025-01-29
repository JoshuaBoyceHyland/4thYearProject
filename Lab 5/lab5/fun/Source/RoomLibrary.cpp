#include "RoomLibrary.h"
RoomLibrary* RoomLibrary::instance = nullptr;

RoomLibrary* RoomLibrary::getInstance()
{
    if (instance == nullptr)
    {
        instance = new RoomLibrary();
    }
    return nullptr;
}

Room* RoomLibrary::getRoom(ResourceType t_type, int index)
{

    return &m_rooms[t_type][index];
}

RoomLibrary::RoomLibrary()
{


}

void RoomLibrary::loadRooms()
{
    Grid m_grid( 10, 10, 100, 100, { -200, -200});
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
