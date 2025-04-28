#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "BehaviourManagert.h"

class NPC : public GameObject
{

	public:
		NPC(Grid* t_map, sf::Vector2f t_position= {-500, -500});

		void update(float deltatime);

		void draw(sf::RenderWindow& t_window);

		void setUpBehaviourTree(Grid* t_map);

	private:

		bool closeToPlayer();

		Grid* m_grid;
		Agent m_agent;
		Animator m_animator;
		BehaviourNode* m_currentBehaviour = nullptr;
		std::unique_ptr<BehaviourNode> m_behaviourTree;
};

