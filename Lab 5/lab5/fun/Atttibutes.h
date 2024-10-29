#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Holds the various variables that will effect flights
/// @param span 
/// </summary>
struct Attributes 
{
	//float span;
	//float weight;
	//float rotation;

	sf::Vector2f* anchorPoint;
	std::vector<sf::Vector2f> connectionPoints;

	Attributes(){}

	Attributes( std::vector<sf::Vector2f> t_connectionPoints)
		:  connectionPoints(t_connectionPoints) {}

	Attributes(const Attributes& other)
	{
		this->anchorPoint = other.anchorPoint;
		this->connectionPoints = connectionPoints;
	}

	sf::Vector2f getAnchoredConnectionPoint(int t_index)
	{
		return (*anchorPoint) + connectionPoints[t_index];
	}

	void visualisePoints(sf::RenderWindow& t_window)
	{

		for (int i = 0; i < connectionPoints.size(); i++)
		{
			sf::CircleShape circle;
			circle.setRadius(2);
			circle.setFillColor(sf::Color::Red);
			circle.setOrigin({ 1, 1 });
			circle.setPosition(getAnchoredConnectionPoint(i));
			t_window.draw(circle);
		}
	}
};