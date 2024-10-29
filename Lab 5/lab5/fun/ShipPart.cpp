#include "ShipPart.h"

ShipPart::ShipPart()
{
}

ShipPart::ShipPart(sf::Texture t_texture, Attributes t_attributes) : m_texture(t_texture), m_attributes(&t_attributes)
{
}

void ShipPart::update()
{
	m_body.setRotation((*m_rotation));
	m_body.setPosition((*m_position));
}

void ShipPart::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
	m_attributes->visualisePoints(t_window);
}

void ShipPart::setConnectionPoint(sf::Vector2f* t_point)
{
	m_connectionPoint = t_point;
}

void ShipPart::setRotation(float* t_rotation)
{
	m_rotation = t_rotation;
}

void ShipPart::setPotation(sf::Vector2f* t_position)
{
	m_position = t_position;
}

void ShipPart::setUp(sf::Texture t_texture, Attributes *t_attributes) 
{
	m_texture = t_texture;
	m_attributes = t_attributes;
	setUpSprite();
}

void ShipPart::setUpSprite()
{
	m_body.setTexture(m_texture);
	m_body.setScale(m_scale);

	m_body.setOrigin({static_cast<float>( m_texture.getSize().x) / 2,static_cast<float>(m_texture.getSize().y) / 2 });

}
