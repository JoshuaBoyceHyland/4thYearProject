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

	float distance = VectorMath::vectorLength( m_ship->getPosition(), t_targetPosition);

}



void SignalIndicaor::draw(sf::RenderWindow& t_winodw)
{
	t_winodw.draw(m_ring);
}
