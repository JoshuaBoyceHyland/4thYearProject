#pragma once
#include "Bullet.h"
#include "Weapons/Weapon.h"
class ShotGun :  public Weapon
{
	public:
		ShotGun(sf::Vector2f& t_holdPoint, Grid* t_grid);
		void shoot() override;
	private:

		int m_pellets = 3;
		int m_shotSpread = 30.0f;


		
};

