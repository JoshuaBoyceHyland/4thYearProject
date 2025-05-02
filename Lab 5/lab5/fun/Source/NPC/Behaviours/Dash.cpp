#include "NPC/Behaviours/Dash.h"

Dash::Dash(Grid* t_grid, Agent* t_agent, Animator* t_animator, bool& t_dashing) : 
	Behaviour(t_grid, t_agent, t_animator),
	m_dashing( t_dashing)
{
	
}


void Dash::startDash()
{

	

	m_agent->m_speed = 10;
	m_animator->m_elapseReset = 4;
	m_animator->m_currentState = 3;


	if (!tryDash(m_dashDirection))
	{
		tryDash(-m_dashDirection);
	}


	std::cout << "Dash started on " << m_animator->m_animations[m_animator->m_currentState].m_currentFrame << std::endl;
	
}
void Dash::endDash()
{
	m_dashing = false;
	m_agent->m_speed = 5;
	m_animator->m_elapseReset = 8;
	std::cout << "Dash finished on " << m_animator->m_animations[m_animator->m_currentState].m_currentFrame << std::endl;
	
}
bool Dash::tryDash(sf::Vector2f t_direction)
{

	sf::Vector2f dash = t_direction * 300.0f;

	for (int i = 0; i < 3; i++)
	{
		sf::Vector2f offset = -t_direction * (100.0f * i);
		sf::Vector2f finalTarget = m_animator->m_sprite.getPosition() + dash + offset;


		Cell* dashTarget = m_grid->cellSelection(finalTarget);

		if (dashTarget != nullptr && dashTarget->getProperty() == TraversalProperty::Walkable)
		{
			m_agent->pathFindTo(dashTarget->getNode());
			return true;
		}
	}
	return false;
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


