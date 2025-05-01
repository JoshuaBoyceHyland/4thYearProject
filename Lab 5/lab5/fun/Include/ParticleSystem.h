#pragma once
#include "Particle.h"
#include <iostream>
class ParticleSystem
{


	public:
		ParticleSystem(sf::Vector2f t_position, sf::Color t_color);

		void update();
		void draw(sf::RenderWindow& t_window);
	private:

		std::vector<Particle> m_particles;
		sf::Clock m_clock;
};

