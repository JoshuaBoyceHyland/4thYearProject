#pragma once
#include "Behaviour.h"

class Talking : public Behaviour
{
	public:
		Talking(Grid* t_grid, Agent* t_agent, Animator* t_animator);

		void update(float t_deltaTime) override;

		void reachedTarget() override;

};

