#include "SignalIndicaor.h"

SignalIndicaor::SignalIndicaor(Ship* t_ship) : m_ship(t_ship)
{

	m_minRadius = t_ship->getRadius();
	m_ring.setRadius(m_minRadius);
	m_ring.setFillColor(sf::Color::Transparent);
	m_ring.setOutlineThickness(2.f);
	m_ring.setOutlineColor(m_color);
	m_ring.setOrigin(m_minRadius, m_minRadius);


	
}

void SignalIndicaor::update(sf::Vector2f t_targetPosition)
{

	m_ring.setPosition(m_ship->getPosition());
	sf::Vector2f toTarget = t_targetPosition - m_ship->getPosition();

	if (VectorMath::vectorLength({ 0, 0 }, toTarget) > 0.01f)
	{
		m_lastTargetDirection = VectorMath::unitVector(toTarget);
	}
}



void SignalIndicaor::draw(sf::RenderWindow& t_winodw)
{
	t_winodw.draw(m_ring);

	sf::CircleShape targetMarker(5.f);
	targetMarker.setFillColor(sf::Color::Magenta);
	targetMarker.setOrigin(5.f, 5.f);
	targetMarker.setPosition(m_ship->getPosition() + m_lastTargetDirection * 100.f); // scale as needed

	t_winodw.draw(targetMarker);

}
