#pragma once
#include "World/Grid.h"
#include"Globals.h"
#include "Utility/RotationMath.h"
#include "Utility/VectorMath.h"
#include <algorithm>

enum class GenerationState { RoomSeperation, RoomCulling, Triangle };

class CircumCircle
{
	public:
		
		CircumCircle(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C)
		{
			double x1 = A.x, y1 = A.y;
			double x2 = B.x, y2 = B.y;
			double x3 = C.x, y3 = C.y;

			double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));


			// not valid and can
			if (std::abs(D) < 1e-6)
			{
				// Colinear case: Construct circle through endpoints and mid-point
				sf::Vector2f midpoint = { (A.x + B.x + C.x) / 3.0f, (A.y + B.y + C.y) / 3.0f };
				float d1 = std::hypot(A.x - midpoint.x, A.y - midpoint.y);
				float d2 = std::hypot(B.x - midpoint.x, B.y - midpoint.y);
				float d3 = std::hypot(C.x - midpoint.x, C.y - midpoint.y);

				radius = std::max({ d1, d2, d3 }) + 1.0f; // Ensure the circle encloses all points
				center = midpoint;
			}
			else
			{
				double X = ((x1 * x1 + y1 * y1) * (y2 - y3) +
					(x2 * x2 + y2 * y2) * (y3 - y1) +
					(x3 * x3 + y3 * y3) * (y1 - y2)) / D;

				double Y = ((x1 * x1 + y1 * y1) * (x3 - x2) +
					(x2 * x2 + y2 * y2) * (x1 - x3) +
					(x3 * x3 + y3 * y3) * (x2 - x1)) / D;

				center = { (float)X, (float)Y };
				radius = std::sqrt((X - x1) * (X - x1) + (Y - y1) * (Y - y1));
			}
			

			circle.setOrigin(radius, radius);
			circle.setRadius(radius);
			circle.setFillColor(sf::Color::Transparent);
			circle.setOutlineColor(sf::Color::Green);
			circle.setOutlineThickness(1);
			circle.setPosition(center);
		}

		bool inCircumCircle(sf::Vector2f point)
		{
			
			return VectorMath::vectorLength(point, center ) < radius;
		}
		void draw(sf::RenderWindow& t_window)
		{
			t_window.draw(circle);
		}

		sf::CircleShape circle;
		float radius;
		sf::Vector2f center;


};


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

		bool triangleIsPoint(sf::Vector2f t_pos)
		{
			for (int i = 0; i < points.size(); i++)
			{
				if (points[i] == t_pos)
				{
					return true;
				}
			}

			return false;

		}

		void draw(sf::RenderWindow& t_window)
		{
			if (drawVis)
			{
				t_window.draw(visualiseation);
			}
			
		}

		sf::VertexArray visualiseation;

		bool drawVis = true;
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
		
		std::vector<sf::CircleShape> sortByDistance(sf::Vector2f position);

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
		
		std::vector<CircumCircle> circsF;
		std::vector<Triangle> trianglesF;
		int current = 0;
};

