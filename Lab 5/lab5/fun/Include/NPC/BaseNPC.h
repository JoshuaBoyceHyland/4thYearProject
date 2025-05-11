#pragma once
#include "NPC/NPC.h"
class BaseNPC : public NPC
{
public:
	BaseNPC(Grid* t_map, BasePlayer* player, sf::Vector2f t_position = { -500, -500 }) :
		NPC(t_map, player, t_position, Base_NPC, "2", {34 ,56})
	{

	}
};

