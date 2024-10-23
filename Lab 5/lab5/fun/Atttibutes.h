#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Holds the various variables that will effect flights
/// @param span 
/// </summary>
struct Attributes 
{
	float span;
	float weight;
	float rotation;

	std::vector<sf::Vector2f> connectionPoints;

	Attributes(){}

	Attributes(float t_span, float t_weight, float t_rotation, std::vector<sf::Vector2f> t_connectionPoints)
		: span(t_span), weight(t_weight), rotation(t_rotation), connectionPoints(t_connectionPoints) {}
};