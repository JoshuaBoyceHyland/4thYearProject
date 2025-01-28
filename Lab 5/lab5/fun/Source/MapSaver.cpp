#include "MapSaver.h"

void MapSaver::saveMap(Grid* t_grid)
{
	std::ofstream file;
	file.open("map.txt");

	if (file.is_open())
	{
    
        for (int row = 0; row < t_grid->m_cells.size(); row++)
        {
            for (int column = 0; column < t_grid->m_cells[row].size(); column++)
            {
                if (t_grid->m_cells[row][column].getTexture() != nullptr)
                {
                    file << row << " " << column << " " << (int)t_grid->m_cells[row][column].getProperty() << " " << t_grid->m_cells[row][column].getTexture()->id << "\n";
                }
               
            }
        }

        file.close();
	}
}

void MapSaver::loadMap(Grid* t_grid)
{
    std::ifstream file;
    file.open("map.txt");

    TileLibrary* library = TileLibrary::getInstance();
    int column, row, type,texture;
    std::string currentLine;

    while (std::getline(file, currentLine))
    {
        std::istringstream stringStream(currentLine);

        stringStream >> row >> column  >> type >> texture;

        Tile* loadedTile = library->getTile(TraversalProperty(type), texture);

        t_grid->m_cells[row][column].setColor(sf::Color::White);
        t_grid->m_cells[row][column].setTexture(loadedTile->m_textures[0]);
        t_grid->m_cells[row][column].setProperty((*loadedTile).m_property);

    }

    file.close();
}
