#include "ShipPart.h"

ShipPart::ShipPart()
{
}

ShipPart::ShipPart(sf::Texture t_texture, PartType t_type, sf::Vector2f t_position) : m_texture(t_texture),m_type(t_type), m_position( t_position)
{

	setUpSprite();
	setUpConnectionPoints();
}

ShipPart::ShipPart(sf::Texture t_texture, Connectors t_attributes) : m_texture(t_texture), m_connectors(&t_attributes)
{
	setUpSprite();
}

bool ShipPart::operator==(const ShipPart& other)
{
	bool sameX = this->m_position.x == other.m_position.x;
	bool sameY = this->m_position.y == other.m_position.y;

	return sameX && sameY;
}

void ShipPart::update()
{

	m_body.setPosition(m_position);
	
}

void ShipPart::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
	m_connectors->visualisePoints(t_window);
}

void ShipPart::setUp(sf::Texture t_texture)
{
	m_texture = t_texture;
	setUpSprite();
	setUpConnectionPoints();
}

void ShipPart::setUp(sf::Texture t_texture, Connectors *t_attributes) 
{
	m_texture = t_texture;
	m_connectors = t_attributes;
	setUpSprite();

}

void ShipPart::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
}

Connectors* ShipPart::getConnectors()
{
	return m_connectors;
}

void ShipPart::setPositionRelativeToConnectorPoint(sf::Vector2f t_position, int t_index)
{

	m_position = t_position - m_connectors->connectionPoints[t_index];
}

sf::Vector2f ShipPart::getPosition()
{
	return m_position;
}


void ShipPart::setUpSprite()
{
	m_body.setTexture(m_texture);
	m_body.setScale(m_scale);
	m_body.setOrigin({static_cast<float>( m_texture.getSize().x) / 2,static_cast<float>(m_texture.getSize().y) / 2 });

}

void ShipPart::setUpConnectionPoints()
{

	m_connectors = new Connectors();

	
	switch (m_type)
	{
	case CockPit:
		m_connectors->connectionPoints.push_back({ 0, static_cast<float>(m_texture.getSize().y * m_body.getScale().y) / 2 });// top
	
		break;
	case Hull:
		m_connectors->connectionPoints.push_back({ -(static_cast<float>(m_texture.getSize().x * m_body.getScale().x) / 2), 0 });// left
		m_connectors->connectionPoints.push_back({ 0, static_cast<float>(m_texture.getSize().y * m_body.getScale().y) / 2 });// top
		m_connectors->connectionPoints.push_back({ (static_cast<float>(m_texture.getSize().x * m_body.getScale().x) / 2), 0 });// right
		m_connectors->connectionPoints.push_back({ 0, -(static_cast<float>(m_texture.getSize().y * m_body.getScale().y) / 2) });// bottom
		break;
	case Left_Wing:
		m_connectors->connectionPoints.push_back({ (static_cast<float>(m_texture.getSize().x * m_body.getScale().x) / 2), 0 });// right
		break;
		
	case Right_Wing:
		m_connectors->connectionPoints.push_back({ -(static_cast<float>(m_texture.getSize().x * m_body.getScale().x) / 2), 0 });// left
		break;
	case Thruster:
		m_connectors->connectionPoints.push_back({ 0, -(static_cast<float>(m_texture.getSize().y * m_body.getScale().y) / 2) });// bottom
		break;
	default:
		break;
	}

	m_connectors->anchorPoint = &m_position;
}
