#include "NPC/Talking.h"

Talking::Talking(Grid* t_grid, Agent* t_agent, Animator* t_animator) : Behaviour( t_grid, t_agent,  t_animator)
{
}

void Talking::update(float t_deltaTime)
{
	m_animator->m_currentState = 0;
}

void Talking::reachedTarget()
{
}
