#pragma once
#include "Globals.h"
#include"SFMl/Graphics.hpp"

class MiniMap
{
	public:
		MiniMap()
		{
			miniMapView.setSize(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);
			miniMapView.setViewport(sf::FloatRect(0.75f, 0.75f, 0.2f, 0.2f));
		}
		void update(sf::Vector2f t_mapCenter)
		{
			miniMapView.setCenter(t_mapCenter);
		}


		sf::View miniMapView;
};

