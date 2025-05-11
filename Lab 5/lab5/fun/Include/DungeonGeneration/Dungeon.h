#pragma once
#include "World/Room.h"
#include "Gameobject.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class Dungeon
{
	public:
		Dungeon(Grid* t_grid, std::vector<Room*> t_rooms);

		void updateIconPos();

		Room* closestRoomTo(sf::Vector2f t_position);
		Grid* m_grid;
	private:

		
		std::vector<Room*> m_rooms;
};

