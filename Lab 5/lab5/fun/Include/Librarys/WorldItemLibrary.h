#pragma once

#include "WorldItems/ShipBuilderTerminal.h"

class WorldItemLibrary
{
	public:

		WorldItemLibrary(const WorldItemLibrary& t_other) = delete;

		static WorldItemLibrary* getInstance();
		
		void setFunction(std::function<void(SceneType)> t_sceneChangeFunction);

		std::function<void(SceneType)>getFunction() { return m_sceneChangeFunction; };

		WorldItem* getItem(int t_index);

		void loadTextures();

		int m_quantity;
	private:

		WorldItemLibrary();

		

		static WorldItemLibrary* instance;

		std::function<void(SceneType)> m_sceneChangeFunction;
		std::vector<WorldItem* > m_items;

};