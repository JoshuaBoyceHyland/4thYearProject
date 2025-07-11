#pragma once
#include "Bullet.h"
#include "Weapons/Weapon.h"
#include "Particles/ParticleSystem.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class MachineGun : public Weapon
{
	public:
		MachineGun(sf::Vector2f& t_holdPoint, Grid* t_grid, Tag t_bulletTag);


		
		void shoot() override;
};

