#include "ShipPart.h"

ShipPart::ShipPart()
{
}

ShipPart::ShipPart(sf::Texture t_texture) : m_texture(t_texture)
{
	setUpSprite();
}

ShipPart::ShipPart(sf::Texture t_texture, Attributes t_attributes) : m_texture(t_texture), m_attributes(&t_attributes)
{
	setUpSprite();
}

void ShipPart::update()
{

	/*m_body.setRotation((*m_rotation));
	m_body.setPosition((*m_position));*/
}

void ShipPart::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
	//m_attributes->visualisePoints(t_window);
}

void ShipPart::setConnectionPoint(sf::Vector2f* t_point)
{
	m_connectionPoint = t_point;
}

void ShipPart::setRotation(float t_rotation)
{
	m_body.setRotation(t_rotation);
}

void ShipPart::setPosition(sf::Vector2f t_position)
{
	m_body.setPosition(t_position);
}

void ShipPart::setUp(sf::Texture t_texture)
{
	m_texture = t_texture;
	setUpSprite();
}

void ShipPart::setUp(sf::Texture t_texture, Attributes *t_attributes) 
{
	m_texture = t_texture;
	m_attributes = t_attributes;
	setUpSprite();
}

void ShipPart::PickUp(sf::Vector2f& t_position)
{
	if (m_body.getGlobalBounds().contains(t_position))
	{
		std::cout << "in bounds" << std::endl;
		m_body.setColor(sf::Color::Green);
	}

}

void ShipPart::setUpSprite()
{
	m_body.setTexture(m_texture);
	m_body.setScale(m_scale);

	m_body.setOrigin({static_cast<float>( m_texture.getSize().x) / 2,static_cast<float>(m_texture.getSize().y) / 2 });

}
