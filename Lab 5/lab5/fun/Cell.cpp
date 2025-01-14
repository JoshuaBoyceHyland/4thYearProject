#include "Cell.h"

Cell::Cell(float t_width, float t_height, sf::Vector2f t_position )
{
	m_body.setPosition(t_position);
	m_body.setSize({t_width, t_height});
	m_body.setFillColor(sf::Color::Transparent);
	m_body.setOutlineColor(sf::Color::Blue);
	m_body.setOutlineThickness(2.5);

	m_property = TraversalProperty::Unwalkable;

	setUpText();
}


void Cell::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
	t_window.draw(m_text);
}

void Cell::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
	m_body.setPosition(m_position);
}

void Cell::setTexture(sf::Texture* t_texture)
{
	
	m_texture = t_texture;
	m_body.setTexture(m_texture);
	m_body.setOutlineThickness(0.0f);
}

void Cell::setProperty(TraversalProperty t_property)
{
	m_property = t_property;
	m_text.setString(m_cellPropertyString[m_property]);
}

void Cell::setUpText()
{
	Loader* loader = Loader::getInstance();

	m_font = loader->loadFont("ASSETS/FONTS/ariblk.ttf");

	m_text.setFont((*m_font));
	m_text.setPosition({ m_body.getPosition().x ,  m_body.getPosition().y + (m_body.getSize().y / 2)});
	m_text.setFillColor(sf::Color::Black);
	m_text.setOutlineColor(sf::Color::Yellow);
	m_text.setOutlineThickness(1.0f);
	m_text.setCharacterSize(m_body.getSize().x * 0.15f);

	m_text.setString(m_cellPropertyString[m_property]);
}
