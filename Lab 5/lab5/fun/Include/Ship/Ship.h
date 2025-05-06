#pragma once
#include "ShipPart.h"
#include "Globals.h"
#include "GameObject.h"
#include "World/Grid.h"
class Ship : public GameObject
{

	public:
		Ship();

		
		void update(float deltaTime);
		void draw(sf::RenderWindow& t_window);
		void setPart(ShipPart t_part);
		void setOrigin(sf::Vector2f t_originPos);
		
		void collisionWith(Tag t_tag) override;
		
		std::vector<Cell*> getCurrentCells(sf::Vector2f t_position);

		void setRotation(float t_rotation) { m_rotation = t_rotation; };
		void setPosition(sf::Vector2f t_position) { m_position = t_position; };
		sf::Vector2f getPosition() { return m_position; };
		float getRotation() { return m_rotation; };
		std::vector<sf::Vector2f> m_offsets;
		std::vector<ShipPart> m_parts;
		std::vector<Grid*> m_grids;
	private:
		
		bool projectPositionIsCollision();
	
		float m_speed = 0;
		float m_rotation = 0; 
		sf::Vector2f m_velocity = { 0, 0 };
		sf::Vector2f m_position = { Globals::SCREEN_WIDTH / 4, Globals::SCREEN_HEIGHT / 4 };
		std::vector<Cell*> m_currentCells ;

		

};

