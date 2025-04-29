#include "NPC/Death.h"

Death::Death(Grid* t_grid, Agent* t_agent, Animator* t_animator) : 
	Behaviour( t_grid, t_agent, t_animator)
{
}

void Death::startDeath()
{
	
	m_animator->m_currentState = 2;
	m_animator->m_assignLasFrame = false;
}

void Death::update(float t_deltaTime)
{

	if (!m_death)
	{
		if (m_animator->animate())
		{
			m_death = true;
		}
	}
		
	
}

void Death::reachedTarget()
{
}
