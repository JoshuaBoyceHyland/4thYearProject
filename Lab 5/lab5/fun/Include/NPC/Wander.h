#pragma once
 
#include "Behaviour.h"


class Wander : public Behaviour
{
	public:

		Wander(Grid* t_grid, Agent* t_agent, Animator* t_animator);

		/// <summary>
		/// Update the wander timer and checking if we should find anotherpoint on the grid to travel to
		/// </summary>
		void update(float t_deltaTime) override;

		/// <summary>
		/// Inherited from Agent user so we can specify what we do simply once we have reached the target
		/// </summary>
		void reachedTarget() override;

		void enter();

		void reset();

	private:

		/// <summary>
		/// Gets a random node on the map to go to
		/// </summary>
		/// <returns>The random node</returns>
		Node* getRandomNode();

		/// <summary>
		/// Whether our timer is up once we arrived somewhere
		/// </summary>
		/// <returns></returns>
		bool timeToFindNewTarget();
		
		/// <summary>
		/// The waiting time between wandering to new place
		/// </summary>
		int m_targetWaitingTime = 1;

		Node* previousTarget = nullptr;

		/// <summary>
		/// Timer for character
		/// </summary>
		sf::Clock m_timer;	

};