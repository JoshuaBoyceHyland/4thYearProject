#pragma once
#include <iostream>
#include "Atttibutes.h"
#include "RotationMath.h"

class Body
{
	public:

		Body(std::string t_texturePath);
		Body(Attributes t_attributes, std::string t_texturePath);
		
		void update();
		void draw(sf::RenderWindow& t_window);
		void setRotation(float t_rotation);
		void setPostion(sf::Vector2f t_position);

	private:

		void setUpBody(std::string t_texturePath);

		sf::Texture m_texture;
		sf::RectangleShape m_body;
		

		Attributes m_attributes;
		std::vector<sf::CircleShape> m_connectionCircles;

		sf::Vector2f m_position;
		float m_rotation;
};

