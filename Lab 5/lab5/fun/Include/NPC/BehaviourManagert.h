#pragma once
#include "Behaviours/Behaviour.h"
#include "Behaviours/Wander.h"
#include "decisionTree/Selector.h"
#include "decisionTree/Sequence.h"
#include "decisionTree/ConditionNodes.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
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
		DecisionNode* m_behaviourTree;
		

};