#include "BasePlayer.h"

BasePlayer::BasePlayer(Grid* t_map) : m_animator("ASSETS/IMAGES/Player"), m_map( t_map)
{
	m_animator.m_sprite.setPosition({ 600, 600 });
}

void BasePlayer::update(float t_deltaTime)
{
	input(t_deltaTime);

	m_animator.animate();

	checkMapInteractions();
}

void BasePlayer::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_animator.m_sprite);
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
			m_animator.m_sprite.setScale({ 1, 1 });
		}
		else
		{
			m_animator.m_sprite.setScale({ -1, 1 });
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
	
	Cell* currentCell = m_map->cellSelection(m_animator.m_sprite.getPosition());
	Cell* projectedCell = m_map->cellSelection(m_animator.m_sprite.getPosition() + m_direction);

	



	// collsion
	if (projectedCell->getProperty() != TraversalProperty::Unwalkable)
	{
		m_animator.m_sprite.setPosition(m_animator.m_sprite.getPosition() + m_direction);


		// resetpreviousCell

		if (currentCell->getNode()->m_column != projectedCell->getNode()->m_column || currentCell->getNode()->m_row != projectedCell->getNode()->m_row)
		{
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
	
		Cell* cell = m_map->cellSelection(m_animator.m_sprite.getPosition());

		cell->setColor(sf::Color::Yellow);
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
