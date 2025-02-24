#pragma once
#include <SFML/Graphics.hpp>
#include "Librarys/Loader.h"
<<<<<<< Updated upstream
class Job
{
	public:
		Job(std::string t_name, sf::Vector2f t_position);
=======

class WorldItem
{
	public:
		WorldItem(Texture* t_texture, sf::Vector2f t_position = { -100, -100});

		WorldItem(std::string t_name, sf::Vector2f t_position);
>>>>>>> Stashed changes

		void draw(sf::RenderWindow& t_window);
<<<<<<< Updated upstream
=======
		
		void setTexture(Texture* t_texture);

		Texture* getTexture() { return m_texture; };

		sf::Sprite m_sprite;

>>>>>>> Stashed changes

	private:
		sf::Vector2f m_position;
		sf::Vector2f m_workingPosition;
		std::string m_name;
		sf::Text m_text;
		sf::Font* m_font;
};

