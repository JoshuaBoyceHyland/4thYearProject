#pragma once
#include "GameObject.h"
#include "World/Grid.h"
#include "NPC/Actors/Animator.h"
#include "WorldItems/ShipBuilderTerminal.h"
#include "Weapons/MachineGun.h"
#include "Weapons/ShotGun.h"

/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class BasePlayer : public GameObject
{
	public:
		BasePlayer(Grid* t_map);

		void update(float t_deltaTime);

		void draw(sf::RenderWindow& t_window);

		void setPosition(sf::Vector2f t_position) { m_animator.m_sprite.setPosition(t_position); };
		
		sf::Vector2f getPosition() { return m_animator.m_sprite.getPosition(); }
		
		void rotateWeapon(sf::Vector2f t_lookAt);
		
		void fireWeapon();

		
		void collisionWith(Tag t_tag) override;

		void setMap(Grid* t_grid);
private:

		void input(float t_deltaTime);

		void cellManagement();

		void checkMapInteractions();

		float m_speed = 0.5f;
		sf::Vector2f m_direction = { 0, 0 };

		Cell* m_currentCell = nullptr;
		Grid* m_map;
		
		Animator m_animator;
		
		sf::Vector2f m_characterMidOffset = { -10,  15 };
		sf::Vector2f m_gunHoldPoint = { 0,0 };
		Weapon* m_currentWeapon;

		ShotGun* m_shotgun;
		MachineGun* m_machineGun;
};

