#pragma once
#include "Behaviours/Behaviour.h"
#include "Behaviours/Wander.h"
#include "BehaviourTree/Selector.h"
#include "BehaviourTree/Sequence.h"
#include "BehaviourTree/ConditionNodes.h"

class BehaviourManager
{
	public:
		BehaviourManager(Grid* t_grid, sf::Vector2f t_position = {-500, -500});

		void update(float t_deltaTime);

		Agent m_agent;

	private:
		
		bool closeToPlayer() { return false; };
		Grid* m_grid = nullptr;
		Behaviour* m_currentBehaviour = nullptr;
		BehaviourNode* m_behaviourTree;
		

};