#pragma once
#include "ShipPart.h"
#include "Globals.h"
class Ship
{

	public:
		Ship();

		void update(float deltaTime);
		void draw(sf::RenderWindow& t_window);
		void setPart(ShipPart t_part);
		void setOrigin(sf::Vector2f t_originPos);
	private:
		
		std::vector<sf::Vector2f> m_offsets;
		std::vector<ShipPart> m_parts;
		float m_speed = 0;
		float m_rotation = 0; 
		sf::Vector2f m_velocity = { 0, 0 };
		sf::Vector2f m_position = { Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2 };
	
};

