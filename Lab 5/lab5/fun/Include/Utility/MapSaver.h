#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include "World/Grid.h"
#include "Librarys/WorldItemLibrary.h"
#include "Librarys/TileLibrary.h"
#include "json.hpp"



class MapSaver
{
	public:

		void saveMap(Grid* t_grid);
		void saveMapJson(Grid* t_grid);

		void loadMap(Grid* t_grid);
		void loadMapJson(Grid* t_grid);
		
};

