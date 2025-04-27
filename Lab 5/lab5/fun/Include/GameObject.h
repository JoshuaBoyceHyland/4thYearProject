#pragma once
#include "SFML/Graphics.hpp"

enum Tag {Player, Enemy };

class GameObject
{
	public:
		Tag m_tag;
		sf::Sprite m_body;
		
};

