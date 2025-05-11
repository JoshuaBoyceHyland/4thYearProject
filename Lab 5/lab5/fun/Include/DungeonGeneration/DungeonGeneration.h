#pragma once
#include "World/Grid.h"
#include"Globals.h"
#include "Utility/RotationMath.h"
#include "Utility/VectorMath.h"
#include <algorithm>
#include <unordered_set>
#include <queue>
#include "Dungeon.h"
#include "World/Search.h"
enum class GenerationState { RoomSeperation, RoomCulling, DelauneyTriangulation, MinSpanningTree, HallwayGen,TextureApplication, Done };


class DungeonGeneration
{

	public:
		DungeonGeneration();

		/// <summary>
		/// Generates out intial grids which will then get turned into rooms
		/// </summary>
		void generateInitialGrids();

		/// <summary>
		/// Generates a Dungeon and returns it
		/// </summary>
		/// <returns></returns>
		Dungeon* generate();

		/// <summary>
		/// looping through states of seperation step by step using keys
		/// calling relevant functions dependant on the state
		/// </summary>
		void generationLoopStepThrough();

		void draw(sf::RenderWindow& t_window);

		GenerationState state = GenerationState::RoomSeperation;
		
		/// <summary>
		/// Halway width
		/// </summary>
		int m_hallWayPadding = 3;

		// intial generation of grids parameters
		int m_minWidthGridGen = 8;
		int m_maxWidthGridGen = 20;
		int m_minHeightGridGen = 8;
		int m_maxHeightGridGen = 20;

		// final rooms desired min widths and heights
		int m_minRoomWidthFinal = 20;
		int m_minRoomHeightFinal = 12;

	private:
		/// <summary>
		/// applies a caluclated seperation force to the rooms and their colliders
		/// </summary>
		void seperateRooms();

		/// <summary>
		/// calculates the speration force dependent on what rooms each room is currently colliding with
		/// </summary>
		void calculateSeperation();

		/// <summary>
		/// checks the current seperation force of all rooms
		/// if all are zero then the rooms have been seperated enough 
		/// </summary>
		/// <returns> whether all rooms are seperated and dont have colliders overlapping</returns>
		bool allRoomsAreSeperated();

		/// <summary>
		/// Removes rooms of defined sizers which are not desired
		/// </summary>
		void cullRooms();

		/// <summary>
		/// Calculates a delauney triangle which will create a edges between rooms
		/// </summary>
		void delauneyTriangle();

		/// <summary>
		/// Creates a super trianfle which will enclose all rooms which we have genrated
		/// used to create triangulations between rooms in delauney triagnle
		/// </summary>
		/// <returns> vector filled with 3 points which make up our super triangle</returns>
		std::vector<Point> createSuperTriangle();

		/// <summary>
		/// Removes duplicate trianglulations left over in vector for visualisation
		/// </summary>
		void cullDuplicateVisulalTriangles();


		/// <summary>
		/// Adds edges from delauney triangle between rooms to the rooms
		/// </summary>
		void AddEdgesToRooms();

		/// <summary>
		/// Gets the dimensions required to create a grid which will encapsulate all the rooms
		/// </summary>
		void AssignCorners();

		/// <summary>
		/// Generates halways in gird dependent on edges
		/// </summary>
		void generateHallways();

		/// <summary>
		/// creates a halway strip from one cell to another horizonitally
		/// </summary>
		/// <param name="xStart">start cell column</param>
		/// <param name="xEnd">end cell column</param>
		/// <param name="row">row of strip</param>
		void horizontalStrip(int xStart, int xEnd, int row, bool corner);

		/// <summary>
		/// creates a halway strip from one cell to another vertically
		/// </summary>
		/// <param name="yStart">start cell row</param>
		/// <param name="yEnd">end cell row</param>
		/// <param name="col">column of strip</param>
		void verticalStrip(int yStart, int yEnd, int col, bool corner);

		/// <summary>
		/// Gets a random point from within a radius
		/// </summary>
		/// <param name="t_radius">Radius where you would like random point to spawn within</param>
		/// <returns>Position of random point in radisu</returns>
		sf::Vector2f getRandomPointInARadius(float t_radius);

		/// <summary>
		/// Prim minimium spannign tree, greedy search
		/// Used to cut down edges which will then become the final hallways between rooms
		/// </summary>
		/// <returns></returns>
		std::vector<PointEdge> minSpanning();

		/// <summary>
		/// Checks if a list of edges contains another edge
		/// </summary>
		/// <param name="edges"></param>
		/// <param name="e"></param>
		/// <returns></returns>
		bool listContainsEdge(std::vector<PointEdge> edges, PointEdge e);

		/// <summary>
		/// Checks if a passed through edge is part of the super triangle eddges
		/// </summary>
		/// <param name="e"></param>
		/// <returns></returns>
		bool partOfSuperTriangle(PointEdge e);

		/// <summary>
		/// Places the rooms generated into a a grid
		/// </summary>
		void placeEnclosingGrid();

		Cell* DungeonGeneration::getHallywayEntry(int t_roomAId, int t_roomBId);

		void applyTextures();
		

		std::vector<sf::Vector2f> m_seperationForces;

		std::vector<sf::RectangleShape> m_mainRoomCollider;

		std::vector<Grid*> m_gridsGenerated;
		std::vector<sf::RectangleShape> m_roomCollider;

		sf::CircleShape m_spawnRadius;
		sf::VertexArray m_superTriangleVisual;
		std::vector< PointEdge> m_visulalisedEdges;
		std::vector<sf::CircleShape>m_spawnPointVisual;

		std::vector<Triangle> m_finalTriangulations;


		sf::Vector2f gridstart = { 0,0 };
		sf::Vector2f gridEnd = { 0, 0 };
	
		Grid* m_dungeon;
		std::vector<Room*> m_mainRooms;


		

};

