#include "Include/VectorMath.h"

sf::Vector2f VectorMath::unitVector(sf::Vector2f a)
{
	float mag = sqrt((a.x * a.x) + (a.y * a.y));

	sf::Vector2f unit = { a.x / mag, a.y / mag };

	return unit;
}

sf::Vector2f VectorMath::directionVector(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f target = b - a;

	float mag = sqrt((target.x * target.x) + (target.y * target.y));

	sf::Vector2f dirVec = { target.x / mag, target.y / mag };

	return dirVec;
}

sf::Vector2f VectorMath::middleVector(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f middleVector = a + b;
	middleVector = { middleVector.x / 2, middleVector.y / 2 };

	return middleVector;
}

float VectorMath::vectorLength(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f target = b - a;

	float mag = sqrt((target.x * target.x) + (target.y * target.y));

	return mag;
}

float VectorMath::vectorToAngle(sf::Vector2f a)
{
	float radians = atan2f(a.y, a.x);
	float degrees = radians * (180 / 3.141592653589793238463f);
	
	return degrees;

}

float VectorMath::crossProduct(sf::Vector2f a, sf::Vector2f b)
{

	float cross = (a.x * b.x + a.y * b.y);
	return cross;
}
