#pragma once
#include "Utility/VectorMath.h"
#include "NPC/Animator.h"

class Weapon
{
	public :
		Weapon( sf::Vector2f& t_holdPoint) : m_holdingPoint(t_holdPoint) {}
		virtual void update() = 0;
		virtual void startShot() = 0;
		virtual void draw(sf::RenderWindow& t_window) = 0;
		float updateWeaponRotation(sf::Vector2f t_lookDirection);
		sf::Sprite m_body;
	protected:
		

		bool m_firing = false;
		sf::Vector2f& m_holdingPoint;
		
};

