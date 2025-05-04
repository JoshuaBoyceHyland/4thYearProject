#pragma once
#include "Globals.h"
#include "Ship/Ship.h"
#include "World/Grid.h"

#include"SFMl/Graphics.hpp"

class MiniMap
{
	public:
		MiniMap(sf::RenderWindow& t_window, Ship* t_player, Grid** t_base);


		void update();

		void drawContents();

		void drawBorder();


		sf::View& getView() { return m_miniMapView; };

	private:

		sf::Color m_darkBlue = sf::Color(14, 34, 99);
		sf::Color m_lightBlue = sf::Color(209, 255, 255);
		sf::RectangleShape m_border;

		sf::View m_miniMapView;
		sf::RenderWindow& m_window;

		Ship* m_player;
		Grid** m_base;
};

