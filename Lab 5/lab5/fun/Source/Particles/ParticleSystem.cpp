#include "Particles/ParticleSystem.h"

ParticleSystem::ParticleSystem(sf::Color t_color, int t_numOfParticles, int t_timeToLiveMax) :
	m_colour(t_color), 
	m_numOfParticles(t_numOfParticles), 
	m_timeToLiveMax(t_timeToLiveMax)
{
}

void ParticleSystem::update(float t_deltaTime)
{

	m_activeParticles.erase(
		std::remove_if(m_activeParticles.begin(), m_activeParticles.end(),
			[](const std::unique_ptr<ParticleExplosion>& activeParticles)
			{
				return activeParticles->allParticlesInactive();
			}),
		m_activeParticles.end() 
	);

	for (int i = 0; i < m_activeParticles.size(); i++)
	{
		m_activeParticles[i]->update();
	}


}

void ParticleSystem::createParticleExplosion(sf::Vector2f t_position, sf::Vector2f t_direction, float t_spreadAngle )
{
	m_activeParticles.push_back(std::make_unique<ParticleExplosion>(t_position, m_colour, t_direction, m_numOfParticles, t_spreadAngle, m_timeToLiveMax));
}

void ParticleSystem::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_activeParticles.size(); i++)
	{
		m_activeParticles[i]->draw(t_window);
	}
}
