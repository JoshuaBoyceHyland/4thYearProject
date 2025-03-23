#pragma once
#include "Behaviour.h"
#include "Wander.h"
#include "BehaviourTypes.h"
#include "Decision.h"

enum NPCState { Wandering, DamageTake, Working,  };
class BehaviourManager
{
	public:
		BehaviourManager(Grid* t_grid, sf::Vector2f t_position = {-500, -500});

		void update(float t_deltaTime);

		NPCState getCurrentBehaviourType();

		Agent m_agent;

	private:
		
		
		Grid* m_grid = nullptr;
		Behaviour* m_currentBehaviour = nullptr;
		NPCState m_currentState = Wandering;
		std::vector<Decision*> decisionTree;
};