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

void MapSaver::saveMapJson(Grid* t_grid)
{

    std::ofstream file("og.json");


    if (file.is_open()) {
        nlohmann::json jsonData;

        for (int row = 0; row < t_grid->m_cells.size(); row++) {
            for (int column = 0; column < t_grid->m_cells[row].size(); column++) {
                if (t_grid->m_cells[row][column].getTexture() != nullptr) 
                {
                    // defautl to no job
                    int job = -1;
                    
                    if (t_grid->m_cells[row][column].m_cellJob != nullptr)
                    {
                        job = t_grid->m_cells[row][column].m_cellJob->getTexture()->id;
                    }

                    nlohmann::json cellData = {
                        {"row", row},
                        {"column", column},
                        {"property", (int)t_grid->m_cells[row][column].getProperty()},
                        {"texture_id", t_grid->m_cells[row][column].getTexture()->id}, 
                        {"Job",job }
                    };
                    jsonData.push_back(cellData);
                }
            }
        }
        file << jsonData.dump(5); // Pretty-print JSON with 4 spaces of indentation
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

void MapSaver::loadMapJson(Grid* t_grid)
{
    std::ifstream file("og.json");

    if (!file.is_open()) return;

    TileLibrary* tileLibrary = TileLibrary::getInstance();
    WorldItemLibrary* worldItemsLibrary = WorldItemLibrary::getInstance();
    nlohmann::json jsonData;
    file >> jsonData;

    for (const auto& cellData : jsonData) {
        int row = cellData["row"];
        int column = cellData["column"];
        int type = cellData["property"];
        int texture = cellData["texture_id"];
        int jobId = cellData["Job"];



        Tile* LoadedTile = tileLibrary->getTile(TraversalProperty(type), texture);
           

        t_grid->m_cells[row][column].setColor(sf::Color::White);
        t_grid->m_cells[row][column].setTexture(LoadedTile->m_textures[0]);
        t_grid->m_cells[row][column].setProperty(LoadedTile->m_property);

        if (jobId != -1)
        {
          
            WorldItem* loadedItem = worldItemsLibrary->getItem(jobId);
            if (jobId == 0)
            {
                t_grid->m_cells[row][column].m_cellJob = new PlayerInteractableItem(loadedItem->getTexture(), worldItemsLibrary->getFunction());
            }
            else if (jobId == 2)
            {
                t_grid->m_cells[row][column].m_cellJob = new PlayerInteractableItem(loadedItem->getTexture(), worldItemsLibrary->getFunction());
                PlayerInteractableItem* item = static_cast<PlayerInteractableItem*>(t_grid->m_cells[row][column].m_cellJob);
                item->setTargetScene(RoomBuilder);
            }
            else
            {
                
             
                t_grid->m_cells[row][column].m_cellJob = new WorldItem(*loadedItem);
            }
           
            t_grid->m_cells[row][column].m_cellJob->setPosition(t_grid->m_cells[row][column].m_body.getPosition());
        }


           

    }
    file.close();

}
