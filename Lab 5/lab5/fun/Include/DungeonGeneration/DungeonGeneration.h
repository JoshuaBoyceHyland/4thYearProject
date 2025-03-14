#pragma once
#include "World/Grid.h"
#include"Globals.h"
#include "Utility/RotationMath.h"
#include "Utility/VectorMath.h"
#include <algorithm>

enum class GenerationState { RoomSeperation, RoomCulling, Triangle };


class Edge
{
	public: 
		

		Edge(int t_roomIdA, int t_roomIdB) : m_roomIdA(t_roomIdA), m_roomIdB(t_roomIdA) {}
		
		
		int m_roomIdA;
		int m_roomIdB;
};

class DungeonGeneration
{

	public:

		void generateRooms();

		void calculateSeperation();

		void update();

		void seperateRooms();

		bool allRoomsAreSeperated();

		void AssignCorners();
		
		void cullRooms();

		void triangulate();

		void draw(sf::RenderWindow& t_window);

		sf::Vector2f getRandomPointInARadius(float t_radius);

	private:

		
		
		void sortXposes();

		void sort( int start, int end);

		int sorty(int start, int end);

		std::vector<sf::CircleShape> m_centers;

		std::vector<sf::Vector2f> m_seperation;
		std::vector<Grid*> m_mainRooms;
		std::vector<sf::RectangleShape> m_mainRoomCollider;

		std::vector<Grid*> m_subRooms;
		std::vector<sf::RectangleShape> m_subRoomCollider;

		std::vector<Grid*> m_roomsGenerated;
		std::vector<sf::RectangleShape> m_roomCollider;
		sf::CircleShape radius;
		std::vector<sf::CircleShape>t_visuals;

		GenerationState state = GenerationState::RoomSeperation;
		
};

