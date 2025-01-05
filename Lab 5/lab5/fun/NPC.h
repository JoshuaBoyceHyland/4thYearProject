#pragma once
#include <SFML/Graphics.hpp>
#include "Job.h"
class NPC
{


	public:
		NPC();
		void assignJob(Job t_job);
		void update();

	private:

		Job t_job;
		sf::CircleShape m_body;
		
};

