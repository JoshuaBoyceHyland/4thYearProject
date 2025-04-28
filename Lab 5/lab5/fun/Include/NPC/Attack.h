  #pragma once
#include "Behaviour.h"
#include "BasePlayer.h"
class Attack : public Behaviour
{
	public:
		Attack(Grid* t_grid, Agent* t_agent, Animator* t_animator);

		void enter();

		void update(float t_deltaTime) override;

		void reachedTarget() override;

		void exit();

		BasePlayer* m_player;
	private:
		void getPointAroundPlayer();

		
};

