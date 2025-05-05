#include "DungeonGeneration/Dungeon.h"

Dungeon::Dungeon(Grid* t_grid, std::vector<Room*> t_rooms) :
	m_grid( t_grid), 
	m_rooms( t_rooms)
{
	m_grid->m_tag = Enemy_Base;
	m_grid->m_body.setPosition(m_rooms[0]->getCenterCell()->m_body.getPosition());
}

void Dungeon::updateIconPos()
{
	m_grid->m_body.setPosition(m_rooms[0]->getCenterCell()->m_body.getPosition());


}

Room* Dungeon::closestRoomTo(sf::Vector2f t_position)
{
	int closest = 0;
	float closestDistance = VectorMath::vectorLength(t_position, m_rooms[0]->getCenterCell()->m_body.getPosition());
	for (int i = 1; i < m_rooms.size(); i++)
	{
		float distacne = VectorMath::vectorLength(t_position, m_rooms[i]->getCenterCell()->m_body.getPosition());
		
		if (distacne < closestDistance)
		{
			closestDistance = distacne;
			closest = i;
		}
		
	}

	
	return m_rooms[closest];
}

