#pragma once
#include "World/Grid.h"
#include "World/Tile.h"
class TileLibrary
{
	public:
		
		TileLibrary(const TileLibrary& t_other) = delete;

		static TileLibrary* getInstance();

		Tile* getTile(TraversalProperty t_type, int t_index);

		std::map<TraversalProperty, int> m_quantity;

		std::vector<Grid> temp1;
	private:

		TileLibrary();

		void loadTextures();

		Grid splitTextureIntoGrid(Texture* t_texture, TraversalProperty t_property);

		static TileLibrary* instance;

		int m_pixelPerCellWidth = 32;
		int m_pixelPerCellHeight = 32;

		std::map<TraversalProperty, std::vector<Tile>> m_tiles;
		
		std::vector<sf::Texture> tempTexture;
		std::vector<Texture> tempTexture2;
		
		std::map<TraversalProperty, std::string> m_cellPropertyString{ {TraversalProperty::Walkable, "Walkable"}, {TraversalProperty::Unwalkable, "Unwalkable"},{TraversalProperty::Job, "Job"} };;
};

