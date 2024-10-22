#ifndef VECTORMATHS_H
#define VECTORMATHS_H

#include <SFML/Graphics.hpp>

namespace VectorMath {

	sf::Vector2f unitVector(sf::Vector2f a);
	
	sf::Vector2f directionVector(sf::Vector2f a, sf::Vector2f b);

	sf::Vector2f middleVector(sf::Vector2f a, sf::Vector2f b);

	float vectorLength(sf::Vector2f a, sf::Vector2f b);

	float vectorToAngle(sf::Vector2f a);

	float crossProduct(sf::Vector2f a, sf::Vector2f b);
}

#endif