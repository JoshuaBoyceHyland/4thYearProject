#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include "World/Grid.h"
#include "Librarys/TileLibrary.h"



class MapSaver
{
	public:
		void saveMap(Grid* t_grid);

		void loadMap(Grid* t_grid);

		
};

