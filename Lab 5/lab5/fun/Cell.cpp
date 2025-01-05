#include "Cell.h"

Cell::Cell(sf::Vector2f t_position, float t_width, float t_height)
{
	m_body.setPosition(t_position);
	m_body.setSize({t_width, t_height});
	m_body.setFillColor(sf::Color::Transparent);
	m_body.setOutlineColor(sf::Color::Blue);
	m_body.setOutlineThickness(2.5);
}

void Cell::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}
