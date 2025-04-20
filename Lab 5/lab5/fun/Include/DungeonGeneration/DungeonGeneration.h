#pragma once
#include "World/Grid.h"
#include"Globals.h"
#include "Utility/RotationMath.h"
#include "Utility/VectorMath.h"
#include <algorithm>
#include <unordered_set>
#include <queue>
#include "World/Room.h"
enum class GenerationState { RoomSeperation, RoomCulling, Triangle, MinSpanning, HallwayGen, Done };







class DungeonGeneration
{

	public:
		DungeonGeneration();

		void generateRooms();

		void calculateSeperation();

		void update();

		void generateHallways();

		void seperateRooms();

		bool allRoomsAreSeperated();

		void AssignCorners();
		
		void cullRooms();

		void delauneyTriangle();

		void cullTriangles();

		void draw(sf::RenderWindow& t_window);

		sf::Vector2f getRandomPointInARadius(float t_radius);
		GenerationState state = GenerationState::RoomSeperation;
		
		sf::Vector2f pos = { 0,0 };
	private:
		

		std::vector<Point> createSuperTriangle();

		sf::VertexArray lines;
		void sort();
		
		std::vector<Point> sortByDistance(sf::Vector2f position);

		bool inCircle(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f P);

		void minimiumSpanningCircle();

		void straightenEdges();


		/// <summary>
		/// Prim min spanninggp 
		/// greedy search
		/// </summary>
		/// <returns></returns>
		std::vector<PointEdge> minSpanning();

		
		

		bool listContainsEdge(std::vector<PointEdge> edges, PointEdge e);

		bool partOfSuperTriangle(PointEdge e);


		void placeEnclosingGrid();



		double EPSILON = 1e-12;
		

		

		std::vector< PointEdge> edges;

		std::vector<sf::Vector2f> m_seperation;

		
		std::vector<sf::RectangleShape> m_mainRoomCollider;

		std::vector<Grid*> m_subRooms;
		std::vector<sf::RectangleShape> m_subRoomCollider;

		std::vector<Grid*> m_roomsGenerated;
		std::vector<sf::RectangleShape> m_roomCollider;
		sf::CircleShape radius;
		std::vector<sf::CircleShape>t_visuals;


		std::vector<Point> superTrianglePoints;
		sf::VertexArray superTriangle;
		
		std::vector<CircumCircle> circsF;
		std::vector<Triangle> trianglesF;
		int current = 0;


		sf::Vector2f gridstart = { 0,0 };
		sf::Vector2f gridEnd = { 0, 0 };
	
		Grid* enclosingGrid;


		std::vector<Room*> mainRoomRooms;



};

