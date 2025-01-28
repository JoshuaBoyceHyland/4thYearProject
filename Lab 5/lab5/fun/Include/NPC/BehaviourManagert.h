#pragma once
#include "Behaviour.h"
#include "Wander.h"
#include "BehaviourTypes.h"

class BehaviourManager
{
	public:
		BehaviourManager(Grid* t_grid, sf::Vector2f t_position = {-500, -500});

		void update(float t_deltaTime);

		BehaviourType getCurrentBehaviourType();

		Agent m_agent;

	private:
		
		
		Grid* m_grid = nullptr;
		BehaviourType m_currentType;
		Behaviour* m_currentBehaviour = nullptr;
		

};