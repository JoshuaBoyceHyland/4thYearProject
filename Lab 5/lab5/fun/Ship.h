#pragma once
#include "ShipPart.h"
class Ship
{

	public:
		Ship();

		void update(float deltaTime);
		void draw(sf::RenderWindow& t_window);
	private:
		void input();
		void boundCheck();

		std::vector<ShipPart> m_parts;
	
};

