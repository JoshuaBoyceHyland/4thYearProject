#include "Weapons/ShotGun.h"

ShotGun::ShotGun(sf::Vector2f& t_holdPoint, Grid* t_grid) : 
	Weapon(t_holdPoint, { 58 - 18, 10 - 19 }, t_grid, "ASSETS/IMAGES/Weapons", { "/MachineGun" }, { 18,19 }, sf::Color::Yellow, 100, 500)
{
}

void ShotGun::shoot()
{

	const float spreadMidPoint = m_shotSpread / 2.0f;

	float currentRotation = m_body.getRotation();

	for (int i = 0; i < m_pellets; ++i)
	{
	
		float agnleOffset = (m_shotSpread / (m_pellets - 1)) * i;
		float currentBulletOffset = -spreadMidPoint + agnleOffset;
		float bulletAngle = currentRotation + currentBulletOffset;

		sf::Vector2f startPoint = m_animator.m_sprite.getPosition() + RotationMath::rotatedVector(m_shootingPointOffset, bulletAngle);

		sf::Vector2f targetDirection = m_animator.m_sprite.getPosition() + RotationMath::rotatedVector({ m_shootingPointOffset.x * 2.0f, m_shootingPointOffset.y }, bulletAngle);

		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>("ASSETS/IMAGES/Weapons/Ammo/Bullet_Shotgun.png", 20, m_grid);
		bullet->shoot(startPoint, targetDirection);
		m_bulletShot.push_back(std::move(bullet));
	}
}
