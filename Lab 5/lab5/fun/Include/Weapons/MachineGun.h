#pragma once
#include "Bullet.h"
#include "Weapons/Weapon.h"
class MachineGun : public Weapon
{
	public:
		MachineGun(sf::Vector2f& t_holdPoint, Grid* t_grid, Tag t_bulletTag);

		void update(float t_deltaTime) override;
		
		void startShot() override;

		void shoot() override;

		void draw(sf::RenderWindow& t_window) override;

		
	private:

		
		Animator m_animator;


		std::vector < std::unique_ptr<ParticleSystem>> m_particleSystem;
		std::vector < std::unique_ptr<Bullet>> m_bulletShot;
		
		

};

