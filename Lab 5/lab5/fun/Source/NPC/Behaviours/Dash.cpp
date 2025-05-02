#include "NPC/Behaviours/Dash.h"

Dash::Dash(Grid* t_grid, Agent* t_agent, Animator* t_animator, bool& t_dashing) : 
	Behaviour(t_grid, t_agent, t_animator),
	m_dashing( t_dashing)
{
	
}


void Dash::startDash()
{

	sf::Vector2 dashDirection = m_dashDirection * 300.0f;

	m_agent->m_speed = 10;
	
	for (int i = 0; i < 6; i++)
	{
		sf::Vector2 finalDashDirection = dashDirection - (m_dashDirection * (100.0f * i));

		Cell* dashTarget = m_grid->cellSelection(m_animator->m_sprite.getPosition() + finalDashDirection);

		if (dashTarget != nullptr)
		{
			m_agent->pathFindTo(dashTarget->getNode());
			break;
		}
	}
	
	
	
	m_animator->m_elapseReset = 4;
	m_animator->m_currentState = 3;
	std::cout << "Dash started on " << m_animator->m_animations[m_animator->m_currentState].m_currentFrame << std::endl;
	
}
void Dash::endDash()
{
	m_dashing = false;
	m_agent->m_speed = 5;
	m_animator->m_elapseReset = 8;
	std::cout << "Dash finished on " << m_animator->m_animations[m_animator->m_currentState].m_currentFrame << std::endl;
	
}
void Dash::update(float t_deltaTime)
{
	// last fram of dash

	//if (m_animator->m_animations[m_animator->m_currentState].m_currentFrame > 1)
	//{
	m_agent->update(t_deltaTime);
	//}
	
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


