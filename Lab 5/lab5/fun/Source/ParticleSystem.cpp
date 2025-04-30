#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(sf::Vector2f t_position)
{
	for (int i = 0; i < 200; i++)
	{
		// -5 to 5
		float randFloatX = ((rand()%202)-101 ) * 0.01f;
		float randFloatY = ((rand() % 202) - 101) * 0.01f;

		sf::Vector2f randVelocity = { randFloatX, randFloatY };

		int randTTL = rand() % 10001;
		float randRotation = rand() % 360;

		m_particles.push_back(Particle(randTTL,randVelocity, t_position,randRotation, sf::Color::Red, 1, 1));
	}

	m_clock.restart();
}

void ParticleSystem::update()
{
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i].update(m_clock.getElapsedTime().asMilliseconds());
		
	}
}

void ParticleSystem::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i].draw(t_window);
	}
}
