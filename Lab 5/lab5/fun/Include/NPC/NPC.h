#pragma once
#include "Animator.h"
#include "BehaviourManagert.h"

class NPC
{

	public:
		NPC(Grid* t_map, sf::Vector2f t_position= {-500, -500});

		void update(float deltatime);

		void draw(sf::RenderWindow& t_window);
	private:

		Animator m_animator;

		BehaviourManager m_behaviour;
		
};

