#pragma once
#include "Utility/VectorMath.h"
#include "Librarys/Loader.h"
#include "Utility/Texture.h"
#include "GameObject.h"

#include "World/Grid.h"
#include "Particles/ParticleExplosion.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>

class Bullet : public GameObject
{
	public: 
		
		Bullet(std::string t_texturePath, float t_speed, Grid* t_grid, Tag t_tag);

		void update(float t_deltaTime);
		

		bool collisionCheck();

		void shoot(sf::Vector2f t_startPoint, sf::Vector2f t_targetDirection);

		void draw(sf::RenderWindow& t_window);

		void collisionWith(Tag t_tag);
		
		sf::Vector2f m_velocity;
	protected:

		float m_speed = 1;
		

		Cell* currnetCell = nullptr;
		Grid* m_grid = nullptr;

		
};

