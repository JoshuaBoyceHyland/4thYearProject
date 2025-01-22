#pragma once
#include "Agent.h"
#include "Animator.h"
class NPC
{


	public:
		NPC();
		NPC(Grid* t_map, sf::Vector2f t_position= {-500, -500});


		void draw(sf::RenderWindow& t_window);
	private:
		
		sf::Vector2f m_position;

		
		Agent m_agent;
		Animator m_animator;
		Grid* m_map = nullptr;
		
};

