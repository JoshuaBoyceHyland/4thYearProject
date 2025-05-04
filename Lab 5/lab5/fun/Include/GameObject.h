#pragma once
#include "SFML/Graphics.hpp"

enum Tag {Bullet_Player, Bullet_Enemy, Player, Enemy  };

class GameObject
{
	public:
		Tag m_tag;
		sf::Sprite m_body;
		virtual void collisionWith(Tag t_tag) =0;
		
};

