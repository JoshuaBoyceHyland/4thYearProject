#include "Ship/ShipPart.h"

ShipPart::ShipPart()
{
}

ShipPart::ShipPart(Texture* t_texture, PartType t_type, sf::Vector2f t_position) : m_texture(t_texture),m_type(t_type), m_position( t_position)
{
	setUpSprite();
	setUpConnectionPoints();
}
ShipPart::ShipPart(const ShipPart& other)
{
	this->m_position = other.m_position;
	this->m_body = other.m_body;
	this->m_type = other.m_type;
	this->m_connectors = other.m_connectors;
	this->m_texture = other.m_texture;
	this->m_scale = other.m_scale;
	this->m_connectors.anchorPoint = &m_position;
	this->m_body.setTexture((*m_texture).texture); // reseting texture
}


bool ShipPart::operator==(const ShipPart& other)
{
	bool sameX = this->m_position.x == other.m_position.x;
	bool sameY = this->m_position.y == other.m_position.y;
	bool sameType = this->m_type == other.m_type;

	return sameX && sameY && sameType;
}

void ShipPart::update()
{
	m_body.setPosition(m_position);	
	//m_body.setRotation(m_rotation);
}

void ShipPart::move(sf::Vector2f t_moveBy, float t_rotation)
{
	m_rotation = t_rotation;
	for (int i = 0; i < m_connectors.connectionPoints.size(); i++)
	{
		if (m_connectors.connectionPoints[i].connectedTo != nullptr)
		{
			sf::Vector2f t = { 400, 400 };
			m_position = t_moveBy - RotationMath::rotatedVector( m_connectors.connectionPoints[i].connectedTo->position, m_rotation);
			break;
		}
	}
	
}

void ShipPart::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
	//m_connectors.visualisePoints(t_window);
}

void ShipPart::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
}

void ShipPart::setPositionRelativeToConnectorPoint(sf::Vector2f t_position, int t_index)
{

	m_position = t_position - m_connectors.connectionPoints[t_index].position;
}

sf::Vector2f ShipPart::getPosition()
{
	
	return m_position;
}

Connector* ShipPart::getConnectors()
{
	return &m_connectors;
}

void ShipPart::setUpSprite()
{
	m_body.setTexture((*m_texture).texture);
	m_body.setScale(m_scale);
	m_body.setOrigin({static_cast<float>( (*m_texture).texture.getSize().x) / 2,static_cast<float>((*m_texture).texture.getSize().y) / 2 });

}

void ShipPart::setUpConnectionPoints()
{


	switch (m_type)
	{
	case PartType::CockPit:
		m_connectors.connectionPoints.emplace_back(Connection({ 0, static_cast<float>((*m_texture).texture.getSize().y * m_body.getScale().y) / 2 }, &m_position));// top
	
		break;
	case PartType::Hull:
		m_connectors.connectionPoints.emplace_back(Connection({ -(static_cast<float>((*m_texture).texture.getSize().x * m_body.getScale().x) / 2), 0 }, &m_position));// left
		m_connectors.connectionPoints.emplace_back(Connection({ 0, static_cast<float>((*m_texture).texture.getSize().y * m_body.getScale().y) / 2 }, &m_position));// top
		m_connectors.connectionPoints.emplace_back(Connection({ (static_cast<float>((*m_texture).texture.getSize().x * m_body.getScale().x) / 2), 0 }, &m_position));// right
		m_connectors.connectionPoints.emplace_back(Connection({ 0, -(static_cast<float>((*m_texture).texture.getSize().y * m_body.getScale().y) / 2) }, &m_position));// bottom
		break;
	case PartType::Left_Wing:
		m_connectors.connectionPoints.emplace_back(Connection({ (static_cast<float>((*m_texture).texture.getSize().x * m_body.getScale().x) / 2), 0 }, &m_position));// right
		break;
		
	case PartType::Right_Wing:
		m_connectors.connectionPoints.emplace_back(Connection({ -(static_cast<float>((*m_texture).texture.getSize().x * m_body.getScale().x) / 2), 0 }, &m_position));// left
		break;
	case PartType::Thruster:
		m_connectors.connectionPoints.emplace_back(Connection({ 0, -(static_cast<float>((*m_texture).texture.getSize().y * m_body.getScale().y) / 2) }, &m_position));// bottom
		break;
	default:
		break;
	}

	m_connectors.anchorPoint = &m_position;
}
