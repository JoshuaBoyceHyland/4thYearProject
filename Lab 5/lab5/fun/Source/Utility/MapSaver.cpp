#include "Utility/MapSaver.h"

void MapSaver::saveMap(Grid* t_grid)
{
	std::ofstream file;
	file.open("og.txt");

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
    file.open("og.txt");

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
<<<<<<< Updated upstream
=======

void MapSaver::loadMapJson(Grid* t_grid)
{
    std::ifstream file("og.json");

    if (!file.is_open()) return;

    TileLibrary* library = TileLibrary::getInstance();
    nlohmann::json jsonData;
    file >> jsonData;

    for (const auto& cellData : jsonData) {
        int row = cellData["row"];
        int column = cellData["column"];
        int type = cellData["property"];
        int texture = cellData["texture_id"];
        int jobId = cellData["Job"];



        //if (jobId != -1)
        //{
        //    Tile* loadedTile = library->getTile(TraversalProperty::Walkable, texture);


        //    t_grid->m_cells[row][column].setColor(sf::Color::White);
        //    t_grid->m_cells[row][column].setTexture(loadedTile->m_textures[0]);
        //    t_grid->m_cells[row][column].setProperty(loadedTile->m_property);

        //    Tile* jobTile = library->getTile(TraversalProperty::Job, jobId);
        //    t_grid->m_cells[row][column].m_cellJob = new WorldItem(jobTile->m_cells[0].m_cellJob->getTexture(), t_grid->m_cells[row][column].m_body.getPosition());
        //}
        //else
        //{
            Tile* loadedTile = library->getTile(TraversalProperty(type), texture);


            t_grid->m_cells[row][column].setColor(sf::Color::White);
            t_grid->m_cells[row][column].setTexture(loadedTile->m_textures[0]);
            t_grid->m_cells[row][column].setProperty(loadedTile->m_property);


            
        //}

    }
    file.close();

}
>>>>>>> Stashed changes
