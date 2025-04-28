#pragma once
#include "Behaviour.h"
#include "BasePlayer.h"
class Attack : public Behaviour
{
	public:
		Attack(Grid* t_grid, Agent* t_agent, Animator* t_animator);
		void update(float t_deltaTime) override;
		void reachedTarget() override;

	private:
		void getPointAroundPlayer();

		BasePlayer* m_player;
};

