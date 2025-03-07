#include "Librarys/RoomLibrary.h"
RoomLibrary* RoomLibrary::instance = nullptr;

RoomLibrary* RoomLibrary::getInstance()
{
    if (instance == nullptr)
    {
        instance = new RoomLibrary();
    }
    return instance;
}

Room* RoomLibrary::getRoom(ResourceType t_type, int index)
{

    return &m_rooms[t_type][index];
}

RoomLibrary::RoomLibrary()
{
    loadRooms();

}

void RoomLibrary::loadRooms()
{
    TileLibrary* library = TileLibrary::getInstance();

    for (int i = 0; i < m_types.size(); i++)
    {
        std::vector<std::string> roomsFilePaths = FileReading::getAllInFile("ASSETS/WORLD_FILES/Rooms/" + m_resourceString[m_types[i]]);

        /*for (std::string roomFileName : roomsFilePaths)
        {
            m_quantity[m_types[i]]++;

            int largestDimension = 0;
            int lastColumn = 0;
            int lastRow = 0;
            const int row = 0;
            const int column = 1;
            const int type = 2;
            const int texture = 3;

            std::vector<std::vector<int>> lines = FileReading::readFile(roomFileName);

            Grid grid(100, 100, 100, 100, { -200, -200 });

            for (std::vector<int> line : lines)
            {
                Tile* loadedTile = library->getTile(TraversalProperty(line[type]), line[texture]);

                grid.m_cells[line[row]][line[column]].setColor(sf::Color::White);
                grid.m_cells[line[row]][line[column]].setTexture(loadedTile->m_textures[0]);
                grid.m_cells[line[row]][line[column]].setProperty((*loadedTile).m_property);
                lastRow = line[row];

                if (lastColumn < line[column])
                {
                    lastColumn = line[column];
                }
            }

            if (lastColumn > lastRow)
            {
                largestDimension = lastColumn;
            }
            else
            {
                largestDimension =lastRow;
            }

            grid.cullEmptyCellsW(largestDimension);
            grid.cullEmptyCellsH(largestDimension);
            m_rooms[m_types[i]].push_back(Room(grid));
        }*/
    }
   

 
}
