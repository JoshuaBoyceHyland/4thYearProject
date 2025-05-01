#pragma once
#include "Utility/VectorMath.h"
#include "Utility/RotationMath.h"
#include "NPC/Animator.h"
#include "World/Grid.h"

class Weapon
{
	public :
		Weapon( sf::Vector2f& t_holdPoint, sf::Vector2f t_shootingPointOffset, Grid* t_grid, std::string t_spriteFolder, std::vector<std::string>t_animationFolderPath, sf::Vector2f t_spriteOrigin, sf::Color t_particleColour) : 
		m_holdingPoint(t_holdPoint), 
		m_shootingPointOffset(t_shootingPointOffset), 
		m_rightShootPoint(t_shootingPointOffset.y), 
		m_grid(t_grid),
		m_animator( t_spriteFolder, t_animationFolderPath, m_body, t_spriteOrigin), 
		m_particleColour(t_particleColour)
		{}
		
	

		virtual void update(float t_deltaTime) = 0;
		
		virtual void startShot() = 0;

		virtual void shoot() = 0;
		
		virtual void draw(sf::RenderWindow& t_window) = 0;
		
		
		float updateWeaponRotation(sf::Vector2f t_lookDirection);


		sf::Sprite m_body;
	protected:
		

		bool m_firing = false;
		
		float m_rightShootPoint = 0;

		Grid* m_grid = nullptr;

		sf::Vector2f m_shootingPointOffset;

		sf::Vector2f& m_holdingPoint;

		sf::Color m_particleColour = sf::Color::Green;

		Animator m_animator;
		
};

