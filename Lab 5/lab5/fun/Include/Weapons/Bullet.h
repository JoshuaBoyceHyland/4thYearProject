#pragma once
#include "Utility/VectorMath.h"
#include "Librarys/Loader.h"
#include "Utility/Texture.h"
#include "GameObject.h"

#include "World/Grid.h"
#include "ParticleSystem.h"


class Bullet : public GameObject
{
	public: 
		
		Bullet(std::string t_texturePath, float t_speed, Grid* t_grid, Tag t_tag) : m_speed(t_speed), m_grid( t_grid)
		{
			Loader* loader = Loader::getInstance();
			Texture* texture = loader->loadTexture(t_texturePath);
			m_tag = t_tag;
			m_body.setTexture(texture->texture);

			m_velocity = { t_speed, t_speed };
		}

		void update(float t_deltaTime)
		{
			
			currnetCell = m_grid->cellSelection(m_body.getPosition() + m_velocity);
		
			m_body.setPosition(m_body.getPosition() + m_velocity);
		}

		bool collisionCheck()
		{
			if (currnetCell->getProperty() == TraversalProperty::Unwalkable)
			{
				
				return true;
			}

			std::unordered_set<GameObject*> gameObjects = currnetCell->getGameObjects();


			for (GameObject* gameObject : gameObjects)
			{
				if (gameObject->m_tag == Tag::Enemy || gameObject->m_tag == Tag::Player)
				{
					if (m_body.getGlobalBounds().intersects(gameObject->m_body.getGlobalBounds()))
					{
						gameObject->collisionWith(m_tag);
						return true;
					}
			
				}


			}

			return false;
		}

		void shoot(sf::Vector2f t_startPoint, sf::Vector2f t_targetDirection)
		{
			m_body.setPosition(t_startPoint);
			sf::Vector2f direction = VectorMath::unitVector(t_targetDirection - t_startPoint );
			float angle = VectorMath::vectorToAngle(direction);
			m_body.setRotation(angle);
			m_velocity = direction * m_speed;

			currnetCell = m_grid->cellSelection(t_startPoint);

			
		}

		void draw(sf::RenderWindow& t_window)
		{
			t_window.draw(m_body);
		}

		void collisionWith(Tag t_tag)
		{

		}
		

	protected:

		float m_speed = 1;
		sf::Vector2f m_velocity;

		Cell* currnetCell = nullptr;
		Grid* m_grid = nullptr;

		
};

