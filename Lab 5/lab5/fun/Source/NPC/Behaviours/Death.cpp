#include "NPC/Behaviours/Death.h"

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
	else
	{
		m_fadeTimer += t_deltaTime;

		if (m_fadeTimer > 50)
		{
			m_fadeTimer = 0;
			sf::Color currentColour = m_animator->m_sprite.getColor();
			currentColour.a = std::max(0.0f, currentColour.a - m_alphaDecrement);

			m_animator->m_sprite.setColor(currentColour);
		}
	}
		
	
}

void Death::reachedTarget()
{
}

void Death::draw(sf::RenderWindow& t_window)
{
}
