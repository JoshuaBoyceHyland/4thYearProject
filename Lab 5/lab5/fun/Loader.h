#pragma once
#include <SFML/Graphics.hpp>
#include <map>;
#include <iostream>

/// <summary>
/// Singleton font and texture loading class
/// Ensures a resource will only be loaded once
/// </summary>
class Loader
{

	public:

		Loader(const Loader& other) = delete;

		/// <summary>
		/// Gets the single instance of this class, if class instance doesn't exist it instaniates it.
		/// </summary>
		/// <returns> Pointer to instance of Loader</returns>
		static Loader* getInstance();

		/// <summary>
		/// Loads the font at the the file path given. 
		/// Checks if the font has already been loaded by checking the font map. 
		/// If it was already loaded it will return the previously loaded font. 
		/// Otherwise it will load the font as expected.
		/// </summary>
		/// <param name="t_path">File location of font</param>
		/// <returns> Pointer to the font</returns>
		sf::Font* loadFont(std::string t_path);

		/// <summary>
		/// Loads the texture at the the file path given. 
		/// Checks if the texture has already been loaded by checking the texture map. 
		/// If it was already loaded it will return the previously loaded texture. 
		/// Otherwise it will load the texture as expected.
		/// </summary>
		/// <param name="t_path">File location of texture</param>
		/// <returns>Pointer to texture</returns>
		sf::Texture* loadTexture(std::string t_path);

	private:
		/// <summary>
		/// Private constructor so it can only created be internally by the getInstance function if needed to.
		/// </summary>
		Loader() = default;

		/// <summary>
		/// Single instance of the loader.
		/// </summary>
		static Loader* instance;

		/// <summary>
		/// Map of fonts, where each font has a associated string key, the string being s file location of the font. This allows the loadFont function to see if te font has been previously loaded.
		/// </summary>
		std::map < std::string, sf::Font> m_fonts;

		/// <summary>
		/// /Map of textures, where each texture has a associated string key, the string being a file location of the texture. This allows the loadtexture function to see if te texture has been previously loaded.
		/// </summary>
		std::map < std::string, sf::Texture> m_textures;

};

