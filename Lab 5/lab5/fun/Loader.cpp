#include "Include/Loader.h"

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
	std::vector<Texture*> textures;
	int id = 0;
	if (std::filesystem::exists(t_path))
	{
		for (auto file : std::filesystem::directory_iterator(t_path))
		{
			std::string fileName = file.path().string();

			if (isPng(fileName))
			{
				std::cout << "Loaded: " << file.path().string() << std::endl;
				textures.push_back(loadTexture(fileName));
				textures[id]->id = id;
				id++;
			}
		}
	}
	else
	{
		std::cout << "Path doesnt exist \n";
	}


	return textures;
}

std::vector<Texture*> Loader::splitAndLoadTexture(std::string t_path, float t_cellWidth, float t_cellHeight)
{
	std::vector<Texture*> splitTextures;
	// load texture
	Texture* texture = loadTexture(t_path);

	splitImage(texture, t_path, t_cellWidth, t_cellHeight);

	for (int i = 0; i < m_splitTextures[t_path].size(); i++)
	{
		splitTextures.push_back(&m_splitTextures[t_path][i]);
	}

	return splitTextures;
}

std::vector<std::vector<Texture*>> Loader::loadAllTexturesInFileSplit(std::string t_path, float t_cellWidth, float t_cellHeight)
{

	std::vector<Texture*> textures = loadAllTexturesInFile(t_path);

	std::vector<std::vector<sf::Texture*>> splitTexttures;

	for (int i = 0; i < textures.size(); i++)
	{
		splitTexttures.push_back(std::vector<sf::Texture*>());
		//splitTexttures[i].push_back( splitImage)
	}


	return std::vector<std::vector<Texture*>>();
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
			for (int row = 0; row < rowsNeeded; row++)
			{
				Texture newTexture;
				sf::IntRect imageArea = sf::IntRect(startX, startY, t_cellWidth, t_cellWidth);

				newTexture.texture.loadFromImage(image, imageArea);
				m_splitTextures[t_path].push_back(newTexture);

				startX += 32;
			}

			startX = 0;
			startY += 32;
		}
	}

}

bool Loader::isPng(std::string t_fileName)
{
	std::vector<char> fileType;
	std::string possiblePng;
	int length = t_fileName.length();

	for (int i = 2; i > -1; i--)
	{
		fileType.push_back(t_fileName[length - (i + 1)]);
	}
	for (int i = 0; i < fileType.size(); i++)
	{
		possiblePng.push_back(fileType[i]);
	}

	if (possiblePng == "png")
	{
		return true;
	}
	
	return false;
}
