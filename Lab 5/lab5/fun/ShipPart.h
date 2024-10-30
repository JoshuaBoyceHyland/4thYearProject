#pragma once
#include <iostream>
#include "Atttibutes.h"
#include "RotationMath.h"

class ShipPart
{
	public:
		ShipPart();
		ShipPart(sf::Texture t_texture);
		ShipPart(sf::Texture t_texture, Attributes t_attributes);

		void update();
		void draw(sf::RenderWindow& t_window);
		void setConnectionPoint(sf::Vector2f* t_point);

		void setRotation(float t_rotation);
		void setPosition(sf::Vector2f t_position);
		void setUp(sf::Texture t_texture);
		void setUp(sf::Texture t_texture, Attributes* t_attributes);

		void PickUp(sf::Vector2f &t_position);

	private:
		void setUpSprite();

		sf::Vector2f m_scale = { 2, 2 };
		sf::Texture m_texture;
		sf::Sprite m_body;

		float* m_rotation;

		sf::Vector2f* m_connectionPoint;
		sf::Vector2f* m_position;
		Attributes* m_attributes;
		

};

