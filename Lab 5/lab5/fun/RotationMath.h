#ifndef ROTATIONMATHS_H
#define ROTATIONMATHS_H

#include <SFML/Graphics.hpp>

namespace RotationMath
{

	const float PI = 3.14159265359;

	/// <summary>
	/// converts degrees to radians
	/// </summary>
	/// <param name="t_degrees"></param>
	/// <returns></returns>
	float degreesToRadians(float t_degrees);

	/// <summary>
	/// converts radians to degrees
	/// </summary>
	/// <param name="t_radians"></param>
	/// <returns></returns>
	float radiansToDegrees(float t_radians);

	/// <summary>
	/// rotates a given vector by the given rotation
	/// </summary>
	/// <param name="t_rotation"> rotations as degrees</param>
	/// <returns></returns>
	sf::Vector2f rotatedVector(sf::Vector2f vector, float t_rotation);

}


#endif