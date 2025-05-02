#include "NPC/Behaviours/Dash.h"

Dash::Dash(Grid* t_grid, Agent* t_agent, Animator* t_animator, bool& t_dashing) : 
	Behaviour(t_grid, t_agent, t_animator),
	m_dashing( t_dashing)
{
	
}


void Dash::startDash()
{
	m_animator->m_currentState = 3;
	std::cout << "Dash started on " << m_animator->m_animations[m_animator->m_currentState].m_currentFrame << std::endl;
	
}
void Dash::endDash()
{

	std::cout << "Dash finished on " << m_animator->m_animations[m_animator->m_currentState].m_currentFrame << std::endl;
	
}
void Dash::update(float t_deltaTime)
{
	// last fram of dash
	if (m_animator->animate(true))
	{
		m_dashing = false;
	}
}

void Dash::reachedTarget()
{
}

void Dash::draw(sf::RenderWindow& t_window)
{
	
}


