#pragma once
#include <SFML/Graphics.hpp>
#include <map>;
#include <iostream>
#include "Loader.h"

class Loader
{

	public:

		Loader(const Loader& other) = delete;

		static Loader* getInstance();

		sf::Font loadFont(std::string t_path);
		sf::Texture loadTexture(std::string t_path);

	private:

		Loader() = default;

		static Loader* instance;
		std::map < std::string, sf::Font> m_fonts;
		std::map < std::string, sf::Texture> m_textures;

};

