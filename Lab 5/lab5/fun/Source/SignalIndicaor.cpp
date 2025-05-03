#include "SignalIndicaor.h"

SignalIndicaor::SignalIndicaor(Ship* t_ship) : m_ship(t_ship)
{

	m_ring.setRadius(100);
	m_ring.setFillColor(sf::Color::Transparent);
	m_ring.setOutlineThickness(2.f);
	m_ring.setOutlineColor(m_color);
	m_ring.setOrigin(100, 100);
}

void SignalIndicaor::update()
{
	m_ring.setPosition(m_ship->getPosition());
}

void SignalIndicaor::draw(sf::RenderWindow& t_winodw)
{
	t_winodw.draw(m_ring);
}
