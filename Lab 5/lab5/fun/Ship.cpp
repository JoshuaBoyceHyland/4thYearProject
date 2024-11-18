#include "Ship.h"

Ship::Ship()
{
}

void Ship::update(float deltaTime)
{
}

void Ship::draw(sf::RenderWindow& t_window)
{
	for ( ShipPart& part : m_parts  )
	{
		part.draw(t_window);
	}
}

void Ship::setPart(ShipPart t_part)
{
	m_parts.push_back(t_part);
}




