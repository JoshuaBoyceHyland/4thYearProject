#include "NPC/NPC.h"

NPC::NPC(Grid* t_map, sf::Vector2f t_position) :  m_behaviour( t_map, t_position)
{
	
	
}


void NPC::update(float deltatime)
{

	m_behaviour.update(deltatime);

	//if (!m_agent.m_hasTarget)
	//{
	//	Node* possibleGoal = m_behaviour.getAction().t_goalNode;

	//	if (possibleGoal != nullptr)
	//	{
	//		m_agent.pathFindTo(possibleGoal);
	//	}
	//	
	//}

	m_animator.animate();

	if (m_behaviour.m_agent.m_direction.x != 0)
	{
		if (m_behaviour.m_agent.m_direction.x > 0)
		{
			m_animator.m_sprite.setScale(1, 1);
		}
		else
		{
			m_animator.m_sprite.setScale(-1, 1);
		}
	}

	if (m_behaviour.m_agent.m_direction.x == 0 && m_behaviour.m_agent.m_direction.y == 0)
	{
		m_animator.m_currentState = 0;
	}
	else
	{
		m_animator.m_currentState = 1;
	}

	m_animator.m_sprite.setPosition(m_behaviour.m_agent.m_position);

}

void NPC::draw(sf::RenderWindow& t_window)
{

	sf::CircleShape t;
	t.setRadius(10);
	t.setOrigin({ 5, 5 });
	t.setFillColor(sf::Color::Magenta);
	t.setPosition(m_behaviour.m_agent.m_position);
	
	t_window.draw(m_animator.m_sprite);
	t_window.draw(t);
}


