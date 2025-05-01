#pragma once
#include "Bullet.h"
#include "Weapons/Weapon.h"
class ShotGun :  public Weapon
{
	public:
		ShotGun(sf::Vector2f& t_holdPoint, Grid* t_grid);
		void update(float t_deltaTime) override;
		void startShot() override;
		void shoot() override;
		void draw(sf::RenderWindow& t_window) override;
	private:

		int m_pellets = 3;
		int m_shotSpread = 30.0f;
		std::vector < std::unique_ptr<ParticleSystem>> m_particleSystem;
		std::vector < std::unique_ptr<Bullet>> m_bulletShot;
};

