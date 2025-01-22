#pragma once
#include "Agent.h"
#include "Animator.h"
class NPC
{


	public:
		NPC();
		NPC(Grid* t_map, sf::Vector2f t_position= {-500, -500});


		void goTo(Node* t_goal);
		void update(float deltatime);

		void draw(sf::RenderWindow& t_window);
	private:
		
		Agent m_agent;
		Animator m_animator;
	
		
};

