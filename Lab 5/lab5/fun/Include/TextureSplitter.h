#pragma once
#include <SFML/Graphics.hpp>
#include "World/Cell.h"
#include "World//Grid.h"

class TextureSplitter
{
	public:
		std::vector<sf::Texture> translateTextureToGrid(sf::Texture* t_texture, float t_cellWidth, float t_cellHeight);
};

