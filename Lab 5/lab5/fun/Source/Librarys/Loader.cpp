#include "Librarys/Loader.h"

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

Texture* Loader::loadTexture(std::string t_path)
{
	if (m_textures.count(t_path) > 0)
	{
		return &m_textures[t_path];
	}

	Texture texture;
	if (!texture.texture.loadFromFile(t_path))
	{
		std::cout << "Could not load texture from " << t_path << std::endl;
	}
	m_textures[t_path] = texture;

	return &m_textures[t_path];
}


std::vector<Texture*> Loader::loadAllTexturesInFile(std::string t_path)
{
	int id = 0;
	std::vector<Texture*> textures;
	std::vector<std::string> fileNames = FileReading::getAllInFile(t_path);

	for (std::string fileName : fileNames)
	{
		if (FileReading::isPNG(fileName))
		{
			std::cout << "Loaded: " << fileName << std::endl;
			textures.push_back(loadTexture(fileName));
			textures[id]->id = id;
			id++;
		}
	}

	return textures;
}


std::vector<std::vector<Texture*>> Loader::splitAllTexturesInFile(std::string t_path, float t_cellWidth, float t_cellHeight)
{

	std::vector<Texture*> textures = loadAllTexturesInFile(t_path);
	std::vector<std::string> fileNames = FileReading::getAllInFile(t_path);
	std::vector<std::vector<Texture*>> vectorOfSplitTextures;

	for (int i = 0; i < textures.size(); i++)
	{
		splitImage(textures[i], t_path + fileNames[i], 32, 32);

		//vectorOfSplitTextures.push_back(m_splitTextures[t_path + fileNames[i]]);
	}


	return vectorOfSplitTextures;
}

void Loader::splitImage(Texture* t_texture, std::string t_path, float t_cellWidth, float t_cellHeight)
{

	if (m_splitTextures.count(t_path) == 0)
	{
		float textureWidth = t_texture->texture.getSize().x;
		float textureHeight = t_texture->texture.getSize().y;

		int columnsNeeded = textureWidth / t_cellWidth;
		int rowsNeeded = textureHeight / t_cellWidth;

		int startX = 0;
		int startY = 0;

		sf::Image image = t_texture->texture.copyToImage();
		std::vector<sf::Texture> textures;

		for (int column = 0; column < columnsNeeded; column++)
		{
			m_splitTextures[t_path].push_back(std::vector<Texture>());

			for (int row = 0; row < rowsNeeded; row++)
			{
				Texture newTexture;
				sf::IntRect imageArea = sf::IntRect(startX, startY, t_cellWidth, t_cellWidth);

				newTexture.texture.loadFromImage(image, imageArea);
				m_splitTextures[t_path][row].push_back(newTexture);

				startX += 32;
			}

			startX = 0;
			startY += 32;
		}
	}

}