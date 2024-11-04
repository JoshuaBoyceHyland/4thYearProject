#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Holds the various variables that will effect flights
/// @param span 
/// </summary>
struct Connectors 
{

	sf::Vector2f* anchorPoint;

	std::vector<sf::Vector2f> connectionPoints;

	Connectors(){}

	Connectors( std::vector<sf::Vector2f> t_connectionPoints)
		:  connectionPoints(t_connectionPoints) {}

	Connectors(const Connectors& other)
	{
		this->anchorPoint = other.anchorPoint;
		this->connectionPoints = connectionPoints;
	}

	std::vector<sf::Vector2f> getAnchoredConnectionPoint()
	{
		std::vector<sf::Vector2f> anchoredPoints;

		for (int i = 0; i < connectionPoints.size(); i++)
		{
			anchoredPoints.push_back((*anchorPoint) + connectionPoints[i]);
		}
		return anchoredPoints;
	}

	void visualisePoints(sf::RenderWindow& t_window)
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
	}
};