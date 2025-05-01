#include "Weapons/MachineGun.h"

MachineGun::MachineGun(sf::Vector2f& t_holdPoint, Grid* t_grid) :
	Weapon( t_holdPoint,{58 - 18, 10 - 19}, t_grid, "ASSETS/IMAGES/Weapons", { "/MachineGun" }, { 18,19 }, sf::Color::Red, 100, 500)
{
	
}

void MachineGun::shoot()
{
	std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>("ASSETS/IMAGES/Weapons/Ammo/Bullet_MachineGun.png", 20 ,m_grid, m_bulletType);
	
	sf::Vector2f ShootPointStart =m_animator.m_sprite.getPosition() + RotationMath::rotatedVector(m_shootingPointOffset, m_body.getRotation());
	sf::Vector2f targetDirection = (m_animator.m_sprite.getPosition() + (RotationMath::rotatedVector({ m_shootingPointOffset.x * 2.0f, m_shootingPointOffset.y }, m_body.getRotation())));
	bullet->shoot(ShootPointStart, targetDirection);

	m_bulletShot.push_back(std::move( bullet));
}

