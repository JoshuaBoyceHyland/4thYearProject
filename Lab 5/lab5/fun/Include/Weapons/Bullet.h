#pragma once
#include "Utility/VectorMath.h"
#include "Librarys/Loader.h"
#include "Utility/Texture.h"
#include "GameObject.h"

class Bullet : public GameObject
{
	public: 
		
		Bullet(std::string t_texturePath, float t_speed) : m_speed(t_speed)
		{
			Loader* loader = Loader::getInstance();
			Texture* texture = loader->loadTexture(t_texturePath);
			m_body.setTexture(texture->texture);

			m_velocity = { t_speed, t_speed };
		}

		void update(float t_deltaTime)
		{
			m_body.setPosition(m_body.getPosition() + m_velocity);
		}

		void shoot(sf::Vector2f t_startPoint, sf::Vector2f t_targetDirection)
		{
			m_body.setPosition(t_startPoint);
			sf::Vector2f direction = VectorMath::unitVector(t_targetDirection - t_startPoint );
			float angle = VectorMath::vectorToAngle(direction);
			m_body.setRotation(angle);
			m_velocity = direction * m_speed;
			
		}

		void draw(sf::RenderWindow& t_window)
		{
			t_window.draw(m_body);
		}
		

	protected:

		float m_speed = 1;
		sf::Vector2f m_velocity;
};

