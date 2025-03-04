#pragma once
#include "World/Grid.h"
#include"Globals.h"
#include "Utility/RotationMath.h"
#include "Utility/VectorMath.h"

class DungeonGeneration
{

	public:

		void step1RandomRooms();

		void step2Direction();

		void step3gatherNeighbours();

		void step4Seperation();

		

		void draw(sf::RenderWindow& t_window);

		sf::Vector2f getRandomPointInARadius(float t_radius);

	private:

		std::vector<sf::Vector2f> m_directions;
		std::vector<Grid*> m_roomsGenerated;
		sf::CircleShape radius;
		std::vector<sf::CircleShape>t_visuals;
		
};

