#include "Body.h"

Body::Body(std::string t_texturePath)
{
	
	setUpBody(t_texturePath);
}

Body::Body(Attributes t_attributes, std::string t_texturePath) : m_attributes( t_attributes)
{
	setUpBody(t_texturePath);
}

void Body::update()
{
	m_body.setRotation(m_rotation);
	m_body.setPosition(m_position);
	for (int i = 0; i < m_connectionCircles.size(); i++)
	{
		m_connectionCircles[i].setRotation(m_rotation);
		m_connectionCircles[i].setPosition(m_position + RotationMath::rotatedVector(m_attributes.connectionPoints[i], m_rotation));
	}
}

void Body::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
	for (int i = 0; i < m_attributes.connectionPoints.size(); i++)
	{
		t_window.draw(m_connectionCircles[i]);
	}
}

void Body::setRotation(float t_rotation)
{
	m_rotation = t_rotation;
}

void Body::setPostion(sf::Vector2f t_position)
{
	m_position = t_position;

}

void Body::setUpBody(std::string t_texturePath)
{
	if (!m_texture.loadFromFile(t_texturePath))
	{
		std::cout << "Cannot load body texture" << std::endl;
	}

	m_body.setTexture(&m_texture);
	//m_body.setFillColor(sf::Color::Blue);
	m_body.setSize({ 100, 100 });
	m_body.setPosition({ 100, 100 });
	m_body.setOrigin({ m_body.getSize().x / 2, m_body.getSize().y / 2 });
	

	m_attributes.connectionPoints.push_back({  - (m_body.getSize().x / 2), 0 });
	m_attributes.connectionPoints.push_back({ ( m_body.getSize().x / 2), 0 });

	for (int i = 0; i < m_attributes.connectionPoints.size(); i++)
	{
		sf::CircleShape circle;
		circle.setRadius(10);
		circle.setFillColor(sf::Color::Red);
		circle.setPosition(m_body.getPosition() + m_attributes.connectionPoints[i]);
		circle.setOrigin({ circle.getRadius() / 2, circle.getRadius() / 2 });
		m_connectionCircles.push_back(circle);
	}

}
