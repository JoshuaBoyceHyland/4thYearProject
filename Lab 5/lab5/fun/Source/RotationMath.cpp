#include "RotationMath.h"

float RotationMath::degreesToRadians(float t_degrees)
{
	float radians = t_degrees * (PI / 180.0f);

	return radians;
}

float RotationMath::radiansToDegrees(float t_radians)
{
	float degrees = t_radians * (180.0f / PI);

	return degrees;
}

sf::Vector2f RotationMath::rotatedVector(sf::Vector2f vector, float t_rotation)
{
	float radians = degreesToRadians(t_rotation);

	sf::Vector2f rotationVector = { std::cos(radians), std::sin(radians) };

	sf::Vector2f rotatedVector = {	vector.x * rotationVector.x - vector.y * rotationVector.y,
									vector.x * rotationVector.y + vector.y * rotationVector.x	};

	return rotatedVector;

}

