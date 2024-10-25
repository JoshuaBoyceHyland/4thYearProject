#pragma once
#include <iostream>
#include "Atttibutes.h"
#include "RotationMath.h"

class Wings
{
	public:
		Wings(std::string t_texturePath );
		Wings(Attributes t_attributes, std::string t_texturePath);

		void update();
		void draw(sf::RenderWindow& t_window);
		void setRotation(float t_rotation);
		void setPostion(sf::Vector2f t_position);
		sf::Vector2f getConnectionPount(int t_index);

	private:

		void setUpBody(std::string t_texturePath);
		void setUpConnectionPoints();

		sf::Texture m_texture;
		sf::ConvexShape m_body;


		Attributes m_attributes;
		std::vector<sf::CircleShape> m_connectionCircles;

		sf::Vector2f m_position;
		float m_rotation;
};

