#pragma once
#include "World/Grid.h"
#include "NPC/Animator.h"
#include "WorldItems/ShipBuilderTerminal.h"
class BasePlayer
{
	public:
		BasePlayer(Grid* t_map);

		void update(float t_deltaTime);

		void draw(sf::RenderWindow& t_window);

		sf::Vector2f getPosition() { return m_animator.m_sprite.getPosition(); }
	private:

		void input(float t_deltaTime);

		void cellManagement();

		void checkMapInteractions();

		float m_speed = 0.5f;
		sf::Vector2f m_direction = { 0, 0 };

		Cell* m_currentCell = nullptr;
		Grid* m_map;
		
		Animator m_animator;
		

};

