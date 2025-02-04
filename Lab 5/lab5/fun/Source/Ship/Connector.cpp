#include "Ship/Connector.h"

Connector::Connector(const Connector& other)
{
	this->anchorPoint = other.anchorPoint;
	this->connectionPoints = connectionPoints;
}

Connector::Connector(std::vector<Connection> t_connectionPoints) : connectionPoints(t_connectionPoints){}

void Connector::visualisePoints(sf::RenderWindow& t_window)
{
	for (int i = 0; i < connectionPoints.size(); i++)
	{
		sf::CircleShape circle;
		circle.setRadius(2);
		circle.setFillColor(sf::Color::Red);
		circle.setOrigin({ 1, 1 });
		circle.setPosition(getAnchoredConnectionPoint()[i]);
		t_window.draw(circle);
	}
	sf::CircleShape circle;
	circle.setRadius(2);
	circle.setFillColor(sf::Color::Red);
	circle.setOrigin({ 1, 1 });
	circle.setPosition((*anchorPoint));
	t_window.draw(circle);
}

std::vector<sf::Vector2f> Connector::getAnchoredConnectionPoint()
{
	std::vector<sf::Vector2f> anchoredPoints;
	
	for (int i = 0; i < connectionPoints.size(); i++)
	{
		anchoredPoints.push_back((*anchorPoint) + connectionPoints[i].position);
	}
	return anchoredPoints;
}
