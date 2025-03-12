#pragma once
#include "World/Grid.h"

class GeneratedRoom
{
	public:
	GeneratedRoom(int t_rows, int t_columns, float t_width, float t_height, sf::Vector2f t_startPosition);
	Grid m_room;
	sf::Vector2f m_center;
	sf::RectangleShape m_collider;

};

