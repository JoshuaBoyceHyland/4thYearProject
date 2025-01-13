#pragma once
#include "Tile.h"
#include "Loader.h"
class TileLibrary
{
	public:
		
		static TileLibrary* getInstance();

	private:

		TileLibrary();

		void loadTextures();

		int rowNumInTexture(sf::Texture* t_texture);
		int colNumInTexture(sf::Texture* t_texture);

		static TileLibrary* instance;




		int m_pixelPerCellWidth = 32;
		int m_pixelPerCellHeight = 32;

		std::map<TraversalProperty, std::vector<Tile>> m_tiles;
		std::map<TraversalProperty, std::string> m_cellPropertyString{ {TraversalProperty::Walkable, "Walkable"}, {TraversalProperty::Unwalkable, "Unwalkable"},{TraversalProperty::Job, "Job"} };;
};

