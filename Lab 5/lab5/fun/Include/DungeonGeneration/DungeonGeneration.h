#pragma once
#include "World/Grid.h"
#include"Globals.h"
#include "Utility/RotationMath.h"
#include "Utility/VectorMath.h"

class DungeonGeneration
{

	public:

		void generateRooms();

		void calculateSeperation();

		void update();

		void seperateRooms();

		bool allRoomsAreSeperated();

		void emplaceRoomsInWorld();
		

		void draw(sf::RenderWindow& t_window);

		sf::Vector2f getRandomPointInARadius(float t_radius);

	private:

		std::vector<sf::Vector2f> m_seperation;
		std::vector<Grid*> m_roomsGenerated;
		std::vector<sf::RectangleShape> m_roomCollider;
		sf::CircleShape radius;
		std::vector<sf::CircleShape>t_visuals;
		
};

