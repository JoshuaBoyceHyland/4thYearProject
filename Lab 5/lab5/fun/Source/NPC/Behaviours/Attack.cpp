#include "NPC/Behaviours/Attack.h"

Attack::Attack(Grid* t_grid, Agent* t_agent, Animator* t_animator) : Behaviour(t_grid, t_agent, t_animator)
{
	m_weapon = new MachineGun( m_gunHoldPoint, t_grid, Bullet_Enemy);
}

void Attack::enter()
{
	getPointAroundPlayer();
}

void Attack::update(float t_deltaTime)
{
	m_weapon->updateWeaponRotation(m_player->getPosition());
	m_weapon->update(t_deltaTime);
	m_agent->update(t_deltaTime);

	m_weapon->startShot();

	

	if (m_player->m_body.getPosition().x > m_animator->m_sprite.getPosition().x)
	{
		m_characterMidOffset.x = -10;
		m_animator->m_sprite.setScale(1, 1);
	}
	else
	{
		m_characterMidOffset.x = 10;
		m_animator->m_sprite.setScale(-1, 1);
	}

	if (m_agent->m_direction.x == 0 && m_agent->m_direction.y == 0)
	{
		m_animator->m_currentState = 0;
	}
	else
	{
		m_animator->m_currentState = 1;
	}

	m_gunHoldPoint = m_animator->m_sprite.getPosition() - m_characterMidOffset;
	m_animator->animate();
}

void Attack::reachedTarget()
{
	getPointAroundPlayer();
}

void Attack::exit()
{
	m_agent->reset();
}

void Attack::draw(sf::RenderWindow& t_window)
{
	m_weapon->draw(t_window);
}

void Attack::getPointAroundPlayer()
{
	Cell* cellAroundPlayer = nullptr;
	Cell* playerCell = m_grid->cellSelection(m_player->getPosition());

	while (cellAroundPlayer == nullptr  )
	{
		std::vector<int> direction = { -1, 0, 1 };
		std::vector<float> distances = { 100, 200, 300, 400, 500 };

		int randXDir = rand() % direction.size();
		int randYDir = rand() % direction.size();

		float randXDistance = rand() % distances.size();
		float randYDistance = rand() % distances.size();


		sf::Vector2f randDirection = { direction[randXDir] * distances[randXDistance],direction[randYDir] * distances[randYDistance] };


		cellAroundPlayer = m_grid->cellSelection(m_player->getPosition() + randDirection);

		
		if (cellAroundPlayer != nullptr );
		{
			bool sameCellAsPlayer = playerCell->getNode()->m_row == cellAroundPlayer->getNode()->m_row && playerCell->getNode()->m_column == cellAroundPlayer->getNode()->m_column;

			if (cellAroundPlayer->getProperty() != TraversalProperty::Walkable || sameCellAsPlayer)
			{
				cellAroundPlayer = nullptr;
			}
		}
	}
	times++;
	std::cout <<"Time: "<< times<< " Row: " << cellAroundPlayer->getNode()->m_row << " Column: " << cellAroundPlayer->getNode()->m_column << " Type: "<< m_grid->m_cells[0][0].m_cellPropertyString[  m_grid->m_cells[cellAroundPlayer->getNode()->m_row][cellAroundPlayer->getNode()->m_column].getProperty()]<< std::endl;
	std::cout << "Currrent " << " Row: " << m_grid->cellSelection(m_animator->m_sprite.getPosition())->getNode()->m_row << " Column: " << m_grid->cellSelection(m_animator->m_sprite.getPosition())->getNode()->m_column << std::endl;
	m_agent->pathFindTo(cellAroundPlayer->getNode());


}
