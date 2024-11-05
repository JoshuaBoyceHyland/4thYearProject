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

