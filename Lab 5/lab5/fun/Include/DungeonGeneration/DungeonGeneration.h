#pragma once
#include "World/Grid.h"
#include"Globals.h"
#include "Utility/RotationMath.h"
#include "Utility/VectorMath.h"
#include <algorithm>

enum class GenerationState { RoomSeperation, RoomCulling, Triangle };



class Triangle
{
	public:
		Triangle() : visualiseation(sf::LineStrip){}

		void addPoint(sf::Vector2f p)
		{
			
			if (size < 3)
			{
				points.push_back(p);
				visualiseation.append(sf::Vertex(p, sf::Color::Red));
				size++;
				if (size == 3)
				{
					visualiseation.append(sf::Vertex(points[0], sf::Color::Red));
				}
			}
		}

		void draw(sf::RenderWindow& t_window)
		{
			t_window.draw(visualiseation);
		}

		sf::VertexArray visualiseation;


		int size = 0;
	
		std::vector<sf::Vector2f> points;
};
class Edge
{
	public: 
		

		Edge(int t_roomIdA, int t_roomIdB) : m_roomIdA(t_roomIdA), m_roomIdB(t_roomIdB) {}
		
		
		int m_roomIdA;
		int m_roomIdB;
};
class PointEdge
{
public:


	PointEdge(sf::Vector2f t_roomIdA, sf::Vector2f t_roomIdB) : m_roomIdA(t_roomIdA), m_roomIdB(t_roomIdB) {}


	sf::Vector2f m_roomIdA;
	sf::Vector2f m_roomIdB;
};
class DungeonGeneration
{

	public:
		DungeonGeneration();
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
		GenerationState state = GenerationState::RoomSeperation;
		
		sf::Vector2f pos = { 0,0 };
	private:
		

		std::vector<sf::Vector2f> createSuperTriangle();

		void detectBadTriangles();

		sf::VertexArray lines;
		void sort();
		
		bool inCircle(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f P);
		double EPSILON = 1e-12;

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

		std::vector<Edge> r;
		std::vector<sf::Vector2f> superTrianglePoints;
		sf::VertexArray superTriangle;
		
		
		std::vector<Triangle> triangles;
};

