#pragma once
#include "Bullet.h"
#include "Weapons/Weapon.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class ShotGun :  public Weapon
{
	public:
		ShotGun(sf::Vector2f& t_holdPoint, Grid* t_grid, Tag t_bulletTag);
		void shoot() override;
	private:

		int m_pellets = 3;
		int m_shotSpread = 30.0f;


		
};

