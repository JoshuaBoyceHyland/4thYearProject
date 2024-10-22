#include "Body.h"

Body::Body(std::string t_texturePath)
{
	
	setUpBody(t_texturePath);
}

Body::Body(Attributes t_attributes, std::string t_texturePath) : m_attributes( t_attributes)
{
	setUpBody(t_texturePath);
}

void Body::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
	for (int i = 0; i < m_attributes.connectionPoints.size(); i++)
	{
		t_window.draw(m_connectionCircles[i]);
	}
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
	

	m_attributes.connectionPoints.push_back({ m_body.getPosition().x - (m_body.getSize().x / 2), m_body.getPosition().y });
	m_attributes.connectionPoints.push_back({ m_body.getPosition().x + (m_body.getSize().x / 2), m_body.getPosition().y });

	for (int i = 0; i < m_attributes.connectionPoints.size(); i++)
	{
		sf::CircleShape circle;
		circle.setRadius(10);
		circle.setFillColor(sf::Color::Red);
		circle.setPosition(m_attributes.connectionPoints[i]);
		circle.setOrigin({ circle.getRadius() / 2, circle.getRadius() / 2 });
		m_connectionCircles.push_back(circle);
	}

}
