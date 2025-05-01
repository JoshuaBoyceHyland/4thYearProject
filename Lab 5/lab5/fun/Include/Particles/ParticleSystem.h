#pragma once
#include "ParticleExplosion.h"



class ParticleSystem
{

	public:
		ParticleSystem(sf::Color t_color, int t_numOfParticles, int t_timeToLiveMax = 1000);

		void update(float t_deltaTime);

		void createParticleExplosion(sf::Vector2f t_position, sf::Vector2f t_direction, float t_spreadAngle = 360.0f);

		void draw(sf::RenderWindow& t_window);

	private:


		sf::Color m_colour;
		int m_timeToLiveMax = 1000;
		float m_particleSpread = 360.0f;
		int m_numOfParticles;
		std::vector < std::unique_ptr<ParticleExplosion>> m_activeParticles;


	
};

