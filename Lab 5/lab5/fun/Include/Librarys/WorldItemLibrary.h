#pragma once

#include "Job.h"

class WorldItemLibrary
{
	public:

		WorldItemLibrary(const WorldItemLibrary& t_other) = delete;

		static WorldItemLibrary* getInstance();

		WorldItem* getItem(int t_index);

		int m_quantity;
	private:

		WorldItemLibrary();

		void loadTextures();

		static WorldItemLibrary* instance;


		std::vector<WorldItem> m_items;

};