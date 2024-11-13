#pragma once
#include <iostream>
#include "Atttibutes.h"
#include "RotationMath.h"

/// <summary>
/// Uses to check what type of ship part this is
/// </summary>
enum class PartType { CockPit = 0, Hull = 1, Left_Wing = 2, Right_Wing = 3, Thruster = 4};

/// <summary>
/// Individual ship parts that can be connected to each other.
/// </summary>
class ShipPart
{
	public:
		ShipPart();

		/// <summary>
		/// Creats a ship part.
		/// </summary>
		/// <param name="t_texture">Reference texture in loader</param>
		/// <param name="t_type">Type of ship part it will be</param>
		/// <param name="t_position">Where it will spawn</param>
		ShipPart(sf::Texture* t_texture,PartType t_type, sf::Vector2f t_position);

		/// <summary>
		/// Copy Constructor.
		/// </summary>
		/// <param name="other">Other Ship</param>
		ShipPart(const ShipPart& other);

		/// <summary>
		/// Compares if ship are the same depending on ship position and type.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator ==(const ShipPart& other);

		/// <summary>
		/// Update position of the ship part.
		/// </summary>
		void update();

		/// <summary>
		/// Draws the ship part and its connection points.
		/// </summary>
		/// <param name="t_window"></param>
		void draw(sf::RenderWindow& t_window);
		
		/// <summary>
		/// Sets the position of the part.
		/// </summary>
		/// <param name="t_position">Desired position</param>
		void setPosition(sf::Vector2f t_position);

		/// <summary>
		/// Sets the position of the shipart relative to the desired connection point.
		/// </summary>
		/// <param name="t_position"> Where the position is being set</param>
		/// <param name="t_index">Which connection point we are position in relative to</param>
		void setPositionRelativeToConnectorPoint(sf::Vector2f t_position, int t_index);

		/// <summary>
		/// Gets the current positon ship.
		/// </summary>
		/// <returns>Current position</returns>
		sf::Vector2f getPosition();

		/// <summary>
		/// Gets the shipParts connector.
		/// </summary>
		/// <returns>Ships connectos</returns>
		Connector* getConnectors();

		/// <summary>
		/// Ship sprite.
		/// </summary>
		sf::Sprite m_body;

		/// <summary>
		/// Reference to ship part texture.
		/// </summary>
		sf::Texture* m_texture;

		/// <summary>
		/// What type of ship part it is.
		/// </summary>
		PartType m_type;

		
	private:

		/// <summary>
		/// Sets up the sprite.
		/// Origin, texture, position .
		/// </summary>
		void setUpSprite();

		/// <summary>
		/// Sets up the connection points dependent on what type of shpart it is.
		/// Cockpit having 1 on the bottom.
		/// Hull haveing 4, 1 on each side.
		/// Thruster having 1 on the top.
		/// Left Wing having 1 on the right.
		/// Right Wing having 1 on the left.
		/// </summary>
		void setUpConnectionPoints();

		/// <summary>
		/// Scale of sprite.
		/// </summary>
		sf::Vector2f m_scale = { 2, 2 };
		
		/// <summary>
		/// Position of Sprite.
		/// </summary>
		sf::Vector2f m_position = { 100, 100 };

		/// <summary>
		/// Ships part connection points.
		/// </summary>
		Connector m_connectors;

		
		

};

