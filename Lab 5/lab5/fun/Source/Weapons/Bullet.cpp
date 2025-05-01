#include "Weapons/Bullet.h"

Bullet::Bullet(std::string t_texturePath, float t_speed, Grid* t_grid, Tag t_tag) : m_speed(t_speed), m_grid(t_grid)
{
	Loader* loader = Loader::getInstance();
	Texture* texture = loader->loadTexture(t_texturePath);
	m_tag = t_tag;
	m_body.setTexture(texture->texture);

	m_velocity = { t_speed, t_speed };
}


void Bullet::update(float t_deltaTime)
{


	if (currnetCell)
	{
		currnetCell->removeGameObject(this);
	}

	currnetCell = m_grid->cellSelection(m_body.getPosition() + m_velocity);

	currnetCell->addToGameObjects(this);
	m_body.setPosition(m_body.getPosition() + m_velocity);
}

bool Bullet::collisionCheck()
{
	if (currnetCell->getProperty() == TraversalProperty::Unwalkable)
	{

		return true;
	}

	std::unordered_set<GameObject*> gameObjects = currnetCell->getGameObjects();


	for (GameObject* gameObject : gameObjects)
	{
		if (gameObject->m_tag == Tag::Enemy || (gameObject->m_tag == Tag::Player && m_tag != Bullet_Player))
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

void Bullet::shoot(sf::Vector2f t_startPoint, sf::Vector2f t_targetDirection)
{
	m_body.setPosition(t_startPoint);
	sf::Vector2f direction = VectorMath::unitVector(t_targetDirection - t_startPoint);
	float angle = VectorMath::vectorToAngle(direction);
	m_body.setRotation(angle);
	m_velocity = direction * m_speed;

	currnetCell = m_grid->cellSelection(t_startPoint);


}

void Bullet::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}

void Bullet::collisionWith(Tag t_tag)
{

}
