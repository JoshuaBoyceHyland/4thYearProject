#include "Loader.h"

Loader* Loader::instance = nullptr;

Loader* Loader::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Loader();
	}
	return instance;
}

sf::Font* Loader::loadFont(std::string t_path)
{

	if (m_fonts.count(t_path) > 0)
	{
		return &m_fonts[t_path];
	}

	sf::Font font;
	if (!font.loadFromFile(t_path))
	{
		std::cout << "Could not load font from " << t_path << std::endl;
	}
	m_fonts[t_path] = font;

	return &m_fonts[t_path];
}

sf::Texture* Loader::loadTexture(std::string t_path)
{
	if (m_textures.count(t_path) > 0)
	{
		return &m_textures[t_path];
	}

	sf::Texture texture;
	if (!texture.loadFromFile(t_path))
	{
		std::cout << "Could not load texture from " << t_path << std::endl;
	}
	m_textures[t_path] = texture;

	return &m_textures[t_path];
}

std::vector<sf::Texture*> Loader::splitAndLoadTexture(std::string t_path)
{
	std::vector<sf::Texture*> splitTextures;
	// load texture
	sf::Texture* texture = loadTexture(t_path);
	
	splitImage(texture, t_path);

	for (int i = 0; i < m_splitTextures[t_path].size(); i++)
	{
		splitTextures.push_back(&m_splitTextures[t_path][i]);
	}

	return splitTextures;
}

void Loader::splitImage(sf::Texture* t_texture, std::string t_path)
{
	float textureWidth = t_texture->getSize().x;
	float textureHeight = t_texture->getSize().y;

	int columnsNeeded = textureWidth / 32;
	int rowsNeeded = textureHeight / 32;

	int startX = 0;
	int startY = 0;
	
	sf::Image image = t_texture->copyToImage();
	std::vector<sf::Texture> textures;

	for (int column = 0; column < columnsNeeded; column++)
	{
		for (int row = 0; row < rowsNeeded; row++)
		{
			sf::Texture newTexture;
			sf::IntRect imageArea = sf::IntRect(startX, startY, 32, 32);

			newTexture.loadFromImage(image, imageArea);
			m_splitTextures[t_path].push_back(newTexture);

			startX += 32;
		}

		startX = 0;
		startY += 32;
	}

}

