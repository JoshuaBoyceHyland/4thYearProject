#pragma once
#include "NPC/Behaviours/Behaviour.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class Death : public Behaviour
{
	public:
		Death(Grid* t_grid, Agent* t_agent, Animator* t_animator);

		void startDeath();
		void update(float t_deltaTime) override;
		void reachedTarget() override;
		void draw(sf::RenderWindow& t_window) override;
	private:
		bool m_death = false;
		float m_fadeTimer = 0;
		float m_fadeFinishTime = 100;
		float m_alphaDecrement = 256 / m_fadeFinishTime;
		
};

