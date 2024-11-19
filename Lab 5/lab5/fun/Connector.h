#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Holds the various variables that will effect flights
/// @param span 
/// </summary>
//struct Connector 
//{
//
//	sf::Vector2f* anchorPoint;
//
//	std::vector<sf::Vector2f> connectionPoints;
//
//	Connector(){}
//
//	Connector( std::vector<sf::Vector2f> t_connectionPoints)
//		:  connectionPoints(t_connectionPoints) {}
//
//	Connector(const Connector& other)
//	{
//		this->anchorPoint = other.anchorPoint;
//		this->connectionPoints = connectionPoints;
//	}
//
//	std::vector<sf::Vector2f> getAnchoredConnectionPoint()
//	{
//		std::vector<sf::Vector2f> anchoredPoints;
//
//		for (int i = 0; i < connectionPoints.size(); i++)
//		{
//			anchoredPoints.push_back((*anchorPoint) + connectionPoints[i]);
//		}
//		return anchoredPoints;
//	}
//
//	void visualisePoints(sf::RenderWindow& t_window)
//	{
//
//		for (int i = 0; i < connectionPoints.size(); i++)
//		{
//			sf::CircleShape circle;
//			circle.setRadius(2);
//			circle.setFillColor(sf::Color::Red);
//			circle.setOrigin({ 1, 1 });
//			circle.setPosition(getAnchoredConnectionPoint()[i]);
//			t_window.draw(circle);
//		}
//	}
//};

struct Connection
{
	sf::Vector2f position;
	Connection* connectedTo = nullptr;

	Connection(sf::Vector2f t_position) : position(t_position) {}
	Connection(const Connection& t_other)
	{
		this->position = t_other.position;
		this->connectedTo = t_other.connectedTo;
	}
};

class Connector
{
	public:

		Connector() = default;
		
		Connector(const Connector& other);

		Connector(std::vector<Connection> t_connectionPoints);

		void visualisePoints(sf::RenderWindow& t_window);

		std::vector<sf::Vector2f> getAnchoredConnectionPoint();

		

		sf::Vector2f* anchorPoint;

		std::vector<Connection> connectionPoints;

};