#include "Weapons/Weapon.h"

float Weapon::updateWeaponRotation(sf::Vector2f t_lookDirection)
{
	float angle = VectorMath::vectorToAngle(t_lookDirection - m_holdingPoint);

	m_body.setRotation(angle);


	if (t_lookDirection.x > m_body.getPosition().x)
	{
		m_shootingPointOffset.y = m_rightShootPoint;
		m_body.setScale({ 1, 1 });
	}
	else
	{
		m_shootingPointOffset.y = -m_rightShootPoint;
		m_body.setScale({ 1, -1 });
	}

	std::cout << angle << std::endl;

	return angle;
}
