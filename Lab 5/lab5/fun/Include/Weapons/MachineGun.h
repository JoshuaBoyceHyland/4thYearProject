#pragma once
#include "Weapons/Weapon.h"
class MachineGun : public Weapon
{
	public:
		MachineGun(sf::Vector2f& t_holdPoint);
		void update() override;
		
		void startShot() override;

		void draw(sf::RenderWindow& t_window) override;

		
	private:

		
		Animator m_animator;

};

