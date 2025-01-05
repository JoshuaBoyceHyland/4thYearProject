#pragma once
#include "Job.h"

class Room
{
	public:
		Room(sf::Vector2f t_position);

		void draw(sf::RenderWindow& t_window);

	private:

		sf::Vector2f m_position;
		std::vector<Job> m_jobs;
		int m_maxJobs = 4;


};

