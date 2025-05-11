  #pragma once
#include "Behaviour.h"
#include "BasePlayer.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class Attack : public Behaviour
{
	public:
		Attack(Grid* t_grid, Agent* t_agent, Animator* t_animator);

		void enter();

		void update(float t_deltaTime) override;

		void reachedTarget() override;

		void exit();

		void draw(sf::RenderWindow& t_window) override;

		BasePlayer* m_player;
	private:

		
		void getPointAroundPlayer();

		Weapon* m_weapon;
		int times = 0;
		sf::Vector2f m_characterMidOffset = { -10,  15 };
		sf::Vector2f m_gunHoldPoint = { 0,0 };
};

