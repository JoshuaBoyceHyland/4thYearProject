#pragma once
#include "Globals.h"
#include "Ship/Ship.h"
#include "World/Grid.h"

#include"SFMl/Graphics.hpp"

class MiniMap
{
	public:
		MiniMap(sf::RenderWindow& t_window, GameObject* t_player, Grid** t_base);


		void update();

		void drawContents();

		void drawBorder();


		sf::View& getView() { return m_miniMapView; };

	private:

		void loadSprites();

		sf::Color m_darkBlue = sf::Color(14, 34, 99);
		sf::Color m_lightBlue = sf::Color(209, 255, 255);
		sf::RectangleShape m_border;

		sf::View m_miniMapView;
		sf::RenderWindow& m_window;

		
		sf::Sprite m_baseSprite;
		sf::Sprite m_playerSprite;

		GameObject* m_player;
		Grid** m_base;

		std::map< Tag, sf::Sprite> m_spriteIcons;

};

