#pragma once
#include "SFML/Graphics.hpp"
class EditorItem 
{
	public:
		virtual void setPosition(sf::Vector2f t_position)=0;
		virtual void draw(sf::RenderWindow& t_window) = 0;
};

