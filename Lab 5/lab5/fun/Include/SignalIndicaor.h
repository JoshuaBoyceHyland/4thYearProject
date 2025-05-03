#pragma once
#include "Ship/Ship.h"

class SignalIndicaor
{
	
	public:
		SignalIndicaor(Ship* t_ship);
		void update(sf::Vector2f t_targetPosition);

		void draw(sf::RenderWindow& t_winodw);

	private:

		sf::Vector2f m_lastTargetDirection = { 0.f, -1.f };
		float m_minRadius = 0;
		sf::CircleShape m_ring;
		sf::Color m_color = sf::Color(0, 255, 255, 150);
		Ship* m_ship;
		sf::Clock m_clock;
};

