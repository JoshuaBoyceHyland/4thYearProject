#pragma once
#include <iostream>
#include "Body.h"
#include <SFML/Graphics.hpp>

class Player 
{
	public:
		Player(sf::Vector2f t_position );
		void update( float deltaTime );
		void draw(sf::RenderWindow& t_window);
		sf::Vector2f getPosition();
		sf::Vector2f getVelocity();

	private:
		void input();
		void boundCheck();
		sf::Vector2f m_position;
		sf::Vector2f m_velocity;
		float m_rotation;
		float m_speed = 0;
		sf::Sprite m_body; 

		sf::Texture m_spriteTexture;

		Body bod;
};

