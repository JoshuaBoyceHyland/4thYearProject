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
    TileLibrary* library = TileLibrary::getInstance();
    std::vector<std::string> roomsFilePaths = FileReading::getAllInFile("ASSETS/WORLD_FILES");

    for (std::string roomFileName : roomsFilePaths)
    {
        
        const int row = 0;
        const int column = 1;
        const int type = 2;
        const int texture = 3;

        std::vector<std::vector<int>> lines = FileReading::readFile("map.txt");

        Grid m_grid(100, 100, 100, 100, { -200, -200 });

        for (std::vector<int> line : lines)
        {
            Tile* loadedTile = library->getTile(TraversalProperty(line[type]), line[texture]);

            m_grid.m_cells[line[row]][line[column]].setColor(sf::Color::White);
            m_grid.m_cells[line[row]][line[column]].setTexture(loadedTile->m_textures[0]);
            m_grid.m_cells[line[row]][line[column]].setProperty((*loadedTile).m_property);
        }

   
    
    }
   

 
}
