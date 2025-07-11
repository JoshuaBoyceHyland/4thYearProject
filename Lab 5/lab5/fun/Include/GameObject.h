#pragma once
#include "SFML/Graphics.hpp"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
enum Tag {Bullet_Player, Bullet_Enemy, Player, Enemy, Player_ship, Enemy_Base, Player_Base, Goal, Base_NPC  };

class GameObject
{
	public:
		Tag m_tag;
		sf::Sprite m_body;
		bool m_active = true;
		virtual void collisionWith(Tag t_tag) =0;
		
};

