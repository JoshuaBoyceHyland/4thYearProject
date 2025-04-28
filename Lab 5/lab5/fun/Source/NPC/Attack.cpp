#include "NPC/Attack.h"

Attack::Attack(Grid* t_grid, Agent* t_agent, Animator* t_animator) : Behaviour(t_grid, t_agent, t_animator)
{

}

void Attack::update(float t_deltaTime)
{
	if (m_player->m_body.getPosition().x > m_animator->m_sprite.getPosition().x)
	{
		m_animator->m_sprite.setScale(1, 1);
	}
	else
	{
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
}

void Attack::reachedTarget()
{
	
}

void Attack::getPointAroundPlayer()
{
	/*Cell* cellAroundPlayer = nullptr;

	while (cellAroundPlayer == nullptr)
	{
		std::vector<int> direction = { -1, 0, 1 };
		std::vector<int> distances = { 100, 200, 300, 400, 500 };

		int randXDir = rand() % direction.size();
		int randYDir = rand() % direction.size();

		int randXDistance = rand() % distances.size();
		int randYDistance = rand() % distances.size();


		sf::Vector2f randDirection = { randXDir * randXDistance,randYDir * randYDistance };


		cellAroundPlayer = m_grid->cellSelection(m_player->getPosition() + randDirection);


		if (cellAroundPlayer != nullptr)
		{
			if (cellAroundPlayer->getProperty() != TraversalProperty::Walkable)
			{
				cellAroundPlayer = nullptr;
			}
		}
	}
	

	m_agent->pathFindTo(cellAroundPlayer->getNode());*/


}
