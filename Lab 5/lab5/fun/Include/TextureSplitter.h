#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
class TextureSplitter
{
	public:
		std::vector<sf::Texture> splitTextureIntoCells(sf::Texture* t_texture, float t_cellWidth, float t_cellHeight);
};

