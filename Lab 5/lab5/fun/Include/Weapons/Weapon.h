#pragma once
#include "Utility/VectorMath.h"
#include "Utility/RotationMath.h"
#include "NPC/Animator.h"
#include "World/Grid.h"

class Weapon
{
	public :
		Weapon( sf::Vector2f& t_holdPoint, sf::Vector2f t_shootingPointOffset, Grid* t_grid, Tag t_tag) : m_holdingPoint(t_holdPoint), m_shootingPointOffset(t_shootingPointOffset), m_rightShootPoint(t_shootingPointOffset.y), m_grid(t_grid), m_bulletType(t_tag){}
		
	

		virtual void update(float t_deltaTime) = 0;
		
		virtual void startShot() = 0;

		virtual void shoot() = 0;
		
		virtual void draw(sf::RenderWindow& t_window) = 0;
		
		
		float updateWeaponRotation(sf::Vector2f t_lookDirection);


		sf::Sprite m_body;
	protected:
		
		Tag m_bulletType = Bullet_Enemy;

		bool m_firing = false;
		
		float m_rightShootPoint = 0;

		Grid* m_grid = nullptr;

		sf::Vector2f m_shootingPointOffset;

		sf::Vector2f& m_holdingPoint;
		
};

