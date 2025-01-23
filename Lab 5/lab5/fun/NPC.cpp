#include "NPC.h"

NPC::NPC(Grid* t_map, sf::Vector2f t_position) :  m_agent ( t_map, t_position)
{
	
}

void NPC::goTo(Node* t_goal)
{
	m_agent.pathFindTo(t_goal);
}

void NPC::update(float deltatime)
{

	m_agent.update(deltatime);

	m_animator.m_sprite.setPosition(m_agent.m_position);

}

void NPC::draw(sf::RenderWindow& t_window)
{

	sf::CircleShape t;
	t.setRadius(10);
	t.setOrigin({ 5, 5 });
	t.setFillColor(sf::Color::Magenta);
	t.setPosition(m_agent.m_position);
	
	t_window.draw(m_animator.m_sprite);
	t_window.draw(t);
}


