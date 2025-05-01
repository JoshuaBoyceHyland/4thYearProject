#include "Weapons/ShotGun.h"

ShotGun::ShotGun(sf::Vector2f& t_holdPoint, Grid* t_grid) : 
	Weapon(t_holdPoint, { 58 - 18, 10 - 19 }, t_grid, "ASSETS/IMAGES/Weapons", { "/Shotgun" }, { 18,19 }, sf::Color::Yellow)
{
}

void ShotGun::update(float t_deltaTime)
{
	m_body.setPosition(m_holdingPoint);

	if (m_firing)
	{

		if (m_animator.animate())
		{
			m_firing = false;

			shoot();

		}
	}

	for (int i = 0; i < m_bulletShot.size(); i++)
	{
		m_bulletShot[i]->update(t_deltaTime);
	}

	// remove bullets if they collide with wall or enems
	m_bulletShot.erase(
		std::remove_if(m_bulletShot.begin(), m_bulletShot.end(),
			[&](const std::unique_ptr<Bullet>& bullet)
			{

				if (bullet->collisionCheck())
				{
					m_particleSystem.push_back(std::make_unique<ParticleSystem>(bullet->m_body.getPosition(), m_particleColour));

					return true;
				}
				return false;


			}),
		m_bulletShot.end()
	);

	for (int i = 0; i < m_particleSystem.size(); i++)
	{
		m_particleSystem[i]->update();
	}
}

void ShotGun::startShot()
{
	if (!m_firing)
	{
		m_firing = true;
	}

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

void ShotGun::draw(sf::RenderWindow& t_window)
{


	sf::CircleShape t(5);
	t.setPosition(m_animator.m_sprite.getPosition());
	t.setOrigin({ 5,5 });
	t.setFillColor(sf::Color::Cyan);


	sf::CircleShape s(5);
	s.setPosition(m_animator.m_sprite.getPosition() + RotationMath::rotatedVector(m_shootingPointOffset, m_body.getRotation()));
	s.setOrigin({ 5,5 });
	s.setFillColor(sf::Color::Cyan);



	sf::Vector2f projected = (m_animator.m_sprite.getPosition() + (RotationMath::rotatedVector({ m_shootingPointOffset.x * 2.0f, m_shootingPointOffset.y }, m_body.getRotation())));
	sf::CircleShape b(5);
	b.setPosition(projected);
	b.setOrigin({ 5,5 });
	b.setFillColor(sf::Color::Cyan);

	t_window.draw(m_animator.m_sprite);



	for (int i = 0; i < m_bulletShot.size(); i++)
	{
		m_bulletShot[i]->draw(t_window);
	}

	for (int i = 0; i < m_particleSystem.size(); i++)
	{
		m_particleSystem[i]->draw(t_window);
	}
}
