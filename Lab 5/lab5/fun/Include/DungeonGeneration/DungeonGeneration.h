#pragma once
#include "World/Grid.h"
class DungeonGenerator
{
	public:
		DungeonGenerator(const DungeonGenerator& t_other) = delete;

		DungeonGenerator* getInstance();
	private:
		static DungeonGenerator* instance;


};