#pragma once
#include <iostream>
#include "Atttibutes.h"
#include "RotationMath.h"
#include "Loader.h"
class CockPit
{

	public:
		CockPit(std::string t_texturePath);
		CockPit(Connector t_attributes, std::string t_texturePath);

		void update();
		void draw(sf::RenderWindow& t_window);
		void setRotation(float t_rotation);
		void setPostion(sf::Vector2f t_position);
		sf::Vector2f getConnectionPount(int t_index);

	private:
		void setUpBody(std::string t_texturePath);
		void setUpConnectionPoints();

		sf::Texture m_texture;
		sf::Sprite m_body;


		Connector m_attributes;
		std::vector<sf::CircleShape> m_connectionCircles;

		sf::Vector2f m_position;
		float m_rotation;

};

