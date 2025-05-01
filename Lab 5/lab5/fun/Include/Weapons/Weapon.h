#pragma once
#include "Utility/VectorMath.h"
#include "Utility/RotationMath.h"
#include "NPC/Actors/Animator.h"
#include "World/Grid.h"
#include "Bullet.h"
#include "Particles/ParticleSystem.h"

class Weapon
{
	public :
		Weapon( sf::Vector2f& t_holdPoint, sf::Vector2f t_shootingPointOffset, Grid* t_grid,
		std::string t_spriteFolder, std::vector<std::string>t_animationFolderPath, sf::Vector2f t_spriteOrigin, 
		sf::Color t_particleColour, int t_numOfParticles, int t_particleTTL, 
			Tag t_bulletType) : 
		m_holdingPoint(t_holdPoint), 
		m_shootingPointOffset(t_shootingPointOffset), 
		m_rightShootPoint(t_shootingPointOffset.y), 
		m_grid(t_grid),
		m_animator( t_spriteFolder, t_animationFolderPath, m_body, t_spriteOrigin),
		m_particleSystem(t_particleColour, t_numOfParticles, t_particleTTL ), 
		m_bulletType(t_bulletType)
		{}
		
		virtual void update(float t_deltaTime);
		
		virtual void startShot();

		virtual void shoot() = 0;
		
		virtual void draw(sf::RenderWindow& t_window);
		
		
		float updateWeaponRotation(sf::Vector2f t_lookDirection);


		sf::Sprite m_body;
	protected:
		
		Tag m_bulletType = Bullet_Enemy;

		bool m_firing = false;
		
		float m_rightShootPoint = 0;

		Grid* m_grid = nullptr;

		sf::Vector2f m_shootingPointOffset;

		sf::Vector2f& m_holdingPoint;

		Animator m_animator;

		std::vector < std::unique_ptr<Bullet>> m_bulletShot;
		ParticleSystem m_particleSystem;
		
};

