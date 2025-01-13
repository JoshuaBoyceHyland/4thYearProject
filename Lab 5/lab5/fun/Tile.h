#pragma once
#include "Cell.h"

class Tile
{

	public:

		Tile(std::vector<sf::Texture*> t_texture, int t_rows, int t_colums);
	private:

		sf::Sprite* m_displayTexture;
		std::vector<Cell> m_cells;
};

