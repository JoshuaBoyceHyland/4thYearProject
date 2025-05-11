#pragma once
#include "Behaviour.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class Dash : public Behaviour
{
	public:
		Dash(Grid* t_grid, Agent* t_agent, Animator* t_animator, bool& t_dashing);
		void update(float t_deltaTime) override;
		void reachedTarget() override;
		void draw(sf::RenderWindow& t_window) override;
		void startDash();
		void endDash();

		

		sf::Vector2f m_dashDirection;
	private:
		bool tryDash(sf::Vector2f t_direction);

		bool& m_dashing;
};

