#include "CockPit.h"

CockPit::CockPit(std::string t_texturePath)
{
	setUpBody(t_texturePath);
	setUpConnectionPoints();
}

CockPit::CockPit(Attributes t_attributes, std::string t_texturePath)
{
	setUpBody(t_texturePath);
}

void CockPit::update()
{
	m_body.setRotation(m_rotation);
	m_body.setPosition(m_position);

	for (int i = 0; i < m_connectionCircles.size(); i++)
	{
		m_connectionCircles[i].setRotation(m_rotation);
		m_connectionCircles[i].setPosition(m_position + RotationMath::rotatedVector(m_attributes.connectionPoints[i], m_rotation));
	}
}

void CockPit::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
	for (int i = 0; i < m_attributes.connectionPoints.size(); i++)
	{
		t_window.draw(m_connectionCircles[i]);
	}
}

void CockPit::setRotation(float t_rotation)
{
	m_rotation = t_rotation;
}

void CockPit::setPostion(sf::Vector2f t_position)
{
	m_position = t_position;
}

sf::Vector2f CockPit::getConnectionPount(int t_index)
{
	return RotationMath::rotatedVector(m_attributes.connectionPoints[t_index], m_rotation);
}

void CockPit::setUpBody(std::string t_texturePath)
{
	Loader* loader = Loader::getInstance();
	m_texture = loader->loadTexture(t_texturePath);

	m_body.setTexture(m_texture);
	m_body.setRotation(m_rotation);
	m_body.setScale({2, 2});
	m_body.setPosition({ 100, 100 });
	m_body.setOrigin({ static_cast<float>(m_texture.getSize().x) / 2,static_cast<float>(m_texture.getSize().y) / 2 });
}

void CockPit::setUpConnectionPoints()
{
	m_attributes.connectionPoints.push_back({ -(static_cast<float>(m_texture.getSize().x * m_body.getScale().x) / 2), 0 });// left
	m_attributes.connectionPoints.push_back({ 0, static_cast<float>(m_texture.getSize().y * m_body.getScale().y) / 2 });// top
	m_attributes.connectionPoints.push_back({ (static_cast<float>(m_texture.getSize().x * m_body.getScale().x) / 2), 0 });// right
	m_attributes.connectionPoints.push_back({ 0, -(static_cast<float>(m_texture.getSize().y * m_body.getScale().y) / 2) });// bottom

	for (int i = 0; i < m_attributes.connectionPoints.size(); i++)
	{
		sf::CircleShape circle;
		circle.setRadius(2);
		circle.setFillColor(sf::Color::Red);
		circle.setPosition(m_body.getPosition() + m_attributes.connectionPoints[i]);
		circle.setOrigin({ circle.getRadius() / 2, circle.getRadius() / 2 });
		m_connectionCircles.push_back(circle);
	}
}
