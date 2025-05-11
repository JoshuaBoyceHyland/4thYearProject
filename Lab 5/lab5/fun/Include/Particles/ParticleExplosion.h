#pragma once
#include "Particle.h"
#include "Utility/RotationMath.h"
#include "Utility/VectorMath.h"
#include <iostream>
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class ParticleExplosion
{


	public:
		ParticleExplosion(sf::Vector2f t_position, sf::Color t_color, sf::Vector2f t_direction,int t_numOfParticles, float t_spreadAngle = 360.0f, int t_timeToLiveMax = 1000);

		void update();
		void draw(sf::RenderWindow& t_window);

		bool allParticlesInactive();
	private:

		std::vector<Particle> m_particles;
		sf::Clock m_clock;
};

