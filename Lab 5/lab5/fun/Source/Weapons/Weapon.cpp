#include "Weapons/Weapon.h"

void Weapon::update(float t_deltaTime)
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

					m_particleSystem.createParticleExplosion(bullet->m_body.getPosition(), -bullet->m_velocity, 180);
					return true;
				}
				return false;


			}),
		m_bulletShot.end()
	);


	m_particleSystem.update(t_deltaTime);
}

void Weapon::startShot()
{
	if (!m_firing)
	{
		m_firing = true;
	}
}

void Weapon::draw(sf::RenderWindow& t_window)
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


	m_particleSystem.draw(t_window);
	for (int i = 0; i < m_bulletShot.size(); i++)
	{
		m_bulletShot[i]->draw(t_window);
	}
}

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
