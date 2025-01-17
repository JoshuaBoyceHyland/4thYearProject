#include "Cell.h"

Cell::Cell(float t_width, float t_height, sf::Vector2f t_position )
{
	m_body.setPosition(t_position);
	m_body.setSize({t_width, t_height});
	m_body.setFillColor(sf::Color::Transparent);
	m_body.setOutlineColor(sf::Color::Blue);
	m_body.setOutlineThickness(2.5);
	//m_body.setOrigin({ t_width / 2, t_height / 2 });
	m_property = TraversalProperty::Unwalkable;

	setUpText();
}

//Cell::Cell(const Cell& t_other)
//{
//	m_body = t_other.m_body;
//	m_position = t_other.m_position;
//	m_property = t_other.m_property;
//	m_text = t_other.m_text;
//	m_texture = t_other.m_texture;
//	m_font = t_other.m_font;
//
//	if (m_texture != nullptr)
//	{
//		m_body.setTexture(&(*m_texture).texture);
//	}
//
//	m_text.setFont((*m_font));
//	
//}


void Cell::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);

	if (m_textActive)
	{
		t_window.draw(m_text);
	}
	
}

void Cell::outlineEnabled(bool t_enable)
{
	if (t_enable)
	{
		m_body.setOutlineThickness(1.0f);
	}
	else
	{
		m_body.setOutlineThickness(0.0f);
	}
}

void Cell::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
	m_body.setPosition(m_position);
}

void Cell::setTexture(Texture* t_texture)
{
	
	m_texture = t_texture;
	m_body.setTexture(&(*m_texture).texture);
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
