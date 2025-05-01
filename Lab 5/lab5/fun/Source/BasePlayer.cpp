#include "BasePlayer.h"

BasePlayer::BasePlayer(Grid* t_map) : 
m_animator("ASSETS/IMAGES/Player", { "/Idle", "/Run"}, m_body, {20.0f, 100.0f}),
m_map(t_map)
{
	m_body.setPosition({ 600, 600 });
	m_tag = Player;

	m_currentWeapon = new ShotGun(m_gunHoldPoint, t_map);
}

void BasePlayer::update(float t_deltaTime)
{
	input(t_deltaTime);

	m_animator.animate();

	checkMapInteractions();
	m_currentWeapon->update(t_deltaTime);
}

void BasePlayer::draw(sf::RenderWindow& t_window)
{
	sf::CircleShape t(10);
	t.setPosition(m_body.getPosition());
	t.setOrigin({ 10,10 });
	t.setFillColor(sf::Color::Cyan);
	

	t_window.draw(t);
	t_window.draw(m_body); 
	m_currentWeapon->draw(t_window);
	
}

void BasePlayer::rotateWeapon(sf::Vector2f t_lookAt)
{
	m_currentWeapon->updateWeaponRotation(t_lookAt);


	if (t_lookAt.x > m_body.getPosition().x)
	{
		m_characterMidOffset.x = -10;
		m_body.setScale({ 1, 1 });
	}
	else
	{
		m_characterMidOffset.x = 10;
		m_body.setScale({ -1, 1 });
	}
}

void BasePlayer::fireWeapon()
{
	m_currentWeapon->startShot();
}

void BasePlayer::input(float t_deltaTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { m_direction.x = -m_speed * t_deltaTime; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { m_direction.x = m_speed * t_deltaTime; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { m_direction.y = -m_speed * t_deltaTime; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { m_direction.y = m_speed * t_deltaTime; }
	

	if (m_direction.x != 0)
	{
		if (m_direction.x > 0)
		{
			m_body.setScale({ 1, 1 });
		}
		else
		{
			m_body.setScale({ -1, 1 });
		}
	}


	if (m_direction.x != 0 || m_direction.y != 0)
	{
		m_animator.m_currentState = 1;
	}
	else
	{
		m_animator.m_currentState = 0;
	}

	cellManagement();
}

void BasePlayer::cellManagement()
{
	
	Cell* currentCell = m_map->cellSelection(m_body.getPosition());
	Cell* projectedCell = m_map->cellSelection(m_body.getPosition() + m_direction);

	
	// collsion
	if (projectedCell->getProperty() != TraversalProperty::Unwalkable)
	{
		m_body.setPosition(m_body.getPosition() + m_direction);

		m_gunHoldPoint = m_body.getPosition() - m_characterMidOffset;
	
		projectedCell->addToGameObjects(this);

		// resetpreviousCell if the current cell and projected cell arent the same
		if (currentCell->getNode()->m_column != projectedCell->getNode()->m_column || currentCell->getNode()->m_row != projectedCell->getNode()->m_row)
		{
			currentCell->removeGameObject(this);
			WorldItem* possibleInteraction = currentCell->m_cellJob;
			
			if (possibleInteraction != nullptr)
			{
				PlayerInteractableItem* interactableItem = static_cast<PlayerInteractableItem*>(possibleInteraction);

				if (possibleInteraction->getPurpose() == Purpose::PlayerInteractable)
				{
					interactableItem->reset();
				}

			}
		}
	}
	m_direction = { 0,0 };
}

void BasePlayer::checkMapInteractions()
{
	
		Cell* cell = m_map->cellSelection(m_body.getPosition());

		//cell->setColor(sf::Color::Yellow);
		WorldItem* possibleInteraction = cell->m_cellJob;

		if (possibleInteraction != nullptr)
		{
			PlayerInteractableItem* interactableItem = static_cast<PlayerInteractableItem*>(possibleInteraction);

			if (possibleInteraction->getPurpose() == Purpose::PlayerInteractable)
			{
				interactableItem->inRangeOfItem();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					interactableItem->use();
				}
			}

		}
		
			
					
					
					
				
	

}

void BasePlayer::collisionWith(Tag t_tag)
{

	if (t_tag == Bullet_Player)
	{

	}
}
