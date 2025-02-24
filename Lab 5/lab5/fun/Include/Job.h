#pragma once
#include <SFML/Graphics.hpp>
#include "Librarys/Loader.h"
#include "World/EditorITem.h"

class WorldItem : public EditorItem
{
	public:
		WorldItem(Texture* t_texture, sf::Vector2f t_position = { -100, -100});

		WorldItem(std::string t_name, sf::Vector2f t_position);


		void draw(sf::RenderWindow& t_window) override;
		
		void setTexture(Texture* t_texture);

		Texture* getTexture() { return m_texture; };


		void setPosition(sf::Vector2f t_position) override;

		sf::Sprite m_sprite;


	private:

		Texture* m_texture;
		sf::Vector2f m_workingPosition;

		std::string m_name;
		sf::Text m_text;
		sf::Font* m_font;
		

	

};

