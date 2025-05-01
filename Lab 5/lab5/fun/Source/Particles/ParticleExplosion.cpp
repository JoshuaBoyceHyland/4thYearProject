#include "Particles/ParticleExplosion.h"

ParticleExplosion::ParticleExplosion(sf::Vector2f t_position, sf::Color t_color, sf::Vector2f t_direction, int t_numOfParticles, float t_spreadAngle, int t_timeToLiveMax)
{

	sf::Vector2f direction  = VectorMath::unitVector(t_direction);

	float directionAngle = VectorMath::vectorToAngle(direction);

	for (int i = 0; i < t_numOfParticles; i++)
	{
		float offset = ((static_cast<float>(rand()) / RAND_MAX) * t_spreadAngle) - (t_spreadAngle / 2.f);

		float angle = directionAngle + offset;

		sf::Vector2f velocity = RotationMath::rotatedVector({ 1.f, 0.f }, angle);

		float randSpeed = static_cast<float>((rand() % 500) + 100) / 100.f; // 1.0 to 6.0
		velocity *= randSpeed;

		int randTTL = rand() % t_timeToLiveMax;
		float randRotation = rand() % 360;

		m_particles.emplace_back(randTTL, velocity, t_position, randRotation, t_color, 1, 1);
	}

	m_clock.restart();
}

void ParticleExplosion::update()
{
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i].update(m_clock.getElapsedTime().asMilliseconds());
	}
}

void ParticleExplosion::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i].draw(t_window);
	}
}

bool ParticleExplosion::allParticlesInactive()
{
	for (int i = 0; i < m_particles.size(); i++)
	{
		if (m_particles[i].m_alive) 
		{
			return false;
		}
	}
	return true;
}
