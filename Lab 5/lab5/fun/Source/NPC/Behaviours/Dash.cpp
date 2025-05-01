#include "NPC/Behaviours/Dash.h"

Dash::Dash(Grid* t_grid, Agent* t_agent, Animator* t_animator, bool& t_dashing) : 
	Behaviour(t_grid, t_agent, t_animator),
	m_dashing( t_dashing)
{
	
}


void Dash::startDash()
{
	m_animator->m_currentState = 3;

	
}
void Dash::update(float t_deltaTime)
{

	m_dashing = m_animator->animate();
}

void Dash::reachedTarget()
{
}

void Dash::draw(sf::RenderWindow& t_window)
{
	
}


