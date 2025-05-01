#pragma once
#include "Behaviour.h"

class Dash : public Behaviour
{
	public:
		Dash(Grid* t_grid, Agent* t_agent, Animator* t_animator, bool& t_dashing);
		void update(float t_deltaTime) override;
		void reachedTarget() override;
		void draw(sf::RenderWindow& t_window) override;
		void startDash();

		sf::Vector2f m_dashDirection;
	private:
		bool& m_dashing;
};

