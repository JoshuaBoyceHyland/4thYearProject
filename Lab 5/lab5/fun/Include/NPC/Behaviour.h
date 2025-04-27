#pragma once
#include "Action.h"
#include "World/Grid.h"
#include "Agent.h"
#include "AgentUser.h"
#include "Animator.h"

class Behaviour : public AgentUser
{
	public:
		Behaviour( Grid* t_grid, Agent* t_agent, Animator* t_animator) : m_grid( t_grid), m_agent( t_agent), m_animator( t_animator){}
		virtual void update(float t_deltaTime) = 0;
		virtual void reachedTarget() = 0;
	protected:

		/// <summary>
		/// The grid of the world where we 
		/// </summary>
		Grid* m_grid = nullptr;

		/// <summary>
		/// The npc that is using the agent, so it can be notified of specific events
		/// </summary>
		Agent* m_agent = nullptr;
		
		Animator* m_animator = nullptr;
};

