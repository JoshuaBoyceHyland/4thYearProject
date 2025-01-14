#include "MapSaver.h"

void MapSaver::saveMap(Grid& t_grid)
{
	std::ofstream file;
	file.open("map.json");

	if (file.is_open())
	{
        file << "{\n";
        file << "  \"cells\": [\n";
        for (int i = 0; i < t_grid.m_cells.size(); i++)
        {
            for (int k = 0; k < t_grid.m_cells[i].size(); k++)
            {
                file << "    { \"id\": "<<k<<", \"type\": "<<(int)t_grid.m_cells[i][k].getProperty()<< "},\n";
            }
            
        }

        file << "  ]\n";
        file << "}\n";
        file.close();
	}
}
