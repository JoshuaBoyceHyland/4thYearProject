#include "Room.h"

Room::Room(sf::Vector2f t_position)
{
	for (int i = 0; i < m_maxJobs; i++)
	{
		m_jobs.emplace_back(Job( "Water Filtration", {100, 100}));
	}
}

void Room::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_maxJobs; i++)
	{
		m_jobs[i].draw(t_window);
	}
}
