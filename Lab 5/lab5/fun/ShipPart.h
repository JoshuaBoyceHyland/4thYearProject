#pragma once
#include <iostream>
#include "Atttibutes.h"
#include "RotationMath.h"

enum class PartType { CockPit = 0, Hull = 1, Left_Wing = 2, Right_Wing = 3, Thruster = 4};

class ShipPart
{
	public:
		ShipPart();
		ShipPart(sf::Texture* t_texture,PartType t_type, sf::Vector2f t_position);
		ShipPart(const ShipPart& other);
		bool operator ==(const ShipPart& other);

		void update();
		void draw(sf::RenderWindow& t_window);
		
		void setPosition(sf::Vector2f t_position);

		Connectors* getConnectors();

		void setPositionRelativeToConnectorPoint(sf::Vector2f t_position, int t_index);

		sf::Vector2f getPosition();

		sf::Sprite m_body;

		sf::Texture* m_texture;

		PartType m_type;

		
	private:
		void setUpSprite();

		void setUpConnectionPoints();

		sf::Vector2f m_scale = { 2, 2 };
		
		

		float* m_rotation;
		
		
		sf::Vector2f m_position = { 100, 100 };
		Connectors* m_connectors;

		
		

};

