#pragma once
#include "NPC/Behaviour.h"

class Death : public Behaviour
{
	public:
		Death(Grid* t_grid, Agent* t_agent, Animator* t_animator);

		void startDeath();
		void update(float t_deltaTime) override;
		void reachedTarget() override;

	private:
		bool m_death = false;
};

