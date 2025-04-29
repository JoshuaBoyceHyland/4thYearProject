#pragma once
#include "Utility/Texture.h"
#include "GameObject.h"

class Bullet : public GameObject
{
	public: 
		
		Bullet(Texture* t_texture, float t_speed) : m_speed( t_speed) 
		{
			//m_body.setTexture(t_texture);
		}
		virtual void shoot(sf::Vector2f t_startPoint, sf::Vector2f t_targetDirection) = 0;
		
	protected:

		float m_speed = 1;
		sf::Vector2f m_velocity;
};

