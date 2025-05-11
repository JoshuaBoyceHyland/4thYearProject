#pragma once
#include "Behaviour.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class Talking : public Behaviour
{
	public:
		Talking(Grid* t_grid, Agent* t_agent, Animator* t_animator);

		void update(float t_deltaTime) override;

		void reachedTarget() override;


		// Inherited via Behaviour
		void draw(sf::RenderWindow& t_window) override;

};

