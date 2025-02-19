#include "TextureSplitter.h"


std::vector<sf::Texture> TextureSplitter::translateTextureToGrid(sf::Texture* t_texture, float t_cellWidth, float t_cellHeight)
{
	float textureWidth = t_texture->getSize().x;
	float textureHeight = t_texture->getSize().y;

	int columnsNeeded = textureWidth / 32;
	int rowsNeeded = textureHeight / 32;


	int startX = 0;
	int startY = 0;
	sf::Texture newTexture;
	sf::IntRect imageArea;
	sf::Image image = t_texture->copyToImage();
	std::vector<sf::Texture> textures;

	for (int column = 0; column < columnsNeeded; column++)
	{
		for (int row = 0; row < rowsNeeded; row++)
		{
			imageArea = sf::IntRect(startX, startY, 32, 32);
			newTexture.loadFromImage(image, imageArea);
			textures.push_back(newTexture);
			startX += 32;
		}

		startX = 0;
		startY += 32;
	}


	return textures;
}
