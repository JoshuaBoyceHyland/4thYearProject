#pragma once
#include <iostream>
#include "Atttibutes.h"
#include "RotationMath.h"

class ShipPart
{
	public:
		ShipPart();
		ShipPart(sf::Texture t_texture, sf::Vector2f t_position);
		ShipPart(sf::Texture t_texture, Connectors t_attributes);

		bool operator ==(const ShipPart& other);

		void update();
		void draw(sf::RenderWindow& t_window);

		void setUp(sf::Texture t_texture);
		void setUp(sf::Texture t_texture, Connectors* t_attributes);
		
		void setPosition(sf::Vector2f t_position);

		Connectors* getConnectors();

		void setPositionRelativeToConnectorPoint(sf::Vector2f t_position, int t_index);

		sf::Vector2f getPosition();

		sf::Sprite m_body;
	private:
		void setUpSprite();
		void setUpConnectionPoints();

		sf::Vector2f m_scale = { 2, 2 };
		sf::Texture m_texture;
		

		float* m_rotation;

		
		sf::Vector2f m_position = { 100, 100 };
		Connectors* m_connectors;

		
		

};

