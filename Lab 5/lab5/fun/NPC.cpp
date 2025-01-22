#include "NPC.h"

NPC::NPC(Grid* t_map, sf::Vector2f t_position) : m_map(t_map), m_position(t_position) 
{
	m_animator.m_sprite.setPosition(t_position);
}

void NPC::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_animator.m_sprite);
}


