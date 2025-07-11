#pragma once
#include "Cell.h"
#include <fstream>
#include <sstream>
#include <string>
#include "Grid.h"
#include <queue>
#include "Librarys/TileLibrary.h"
#include "Utility/VectorMath.h"
#include "Utility/RotationMath.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
enum class ResourceType{  Electricty, Happinness, Water, Oxygen, None};

class CircumCircle
{
public:

	// AI generated
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

		return VectorMath::vectorLength(point, center) < radius;
	}
	void draw(sf::RenderWindow& t_window)
	{
		t_window.draw(circle);
	}

	sf::CircleShape circle;
	float radius;
	sf::Vector2f center;


};



class PointEdge
{
public:


	PointEdge(int t_roomAId, sf::Vector2f t_roomAPos, int t_roomBId, sf::Vector2f t_roomBPos) :
		m_roomAId(t_roomAId), m_roomAPos(t_roomAPos),
		m_roomBId(t_roomBId), m_roomBPos(t_roomBPos),
		visulisations(sf::Lines)
	{
		Loader* l = Loader::getInstance();
		f = l->loadFont("ASSETS/FONTS/nulshock.otf");

		m_text.setFont(*f);
		m_text.setFillColor(sf::Color::White);
		m_text.setCharacterSize(10);
		m_text.setPosition(sf::Vector2f((t_roomAPos.x + t_roomBPos.x) / 2.0f, (t_roomAPos.y + t_roomBPos.y) / 2.0f));

		visulisations.append(sf::Vertex(t_roomAPos, sf::Color::Green));
		visulisations.append(sf::Vertex(t_roomBPos, sf::Color::Green));
		cost = std::sqrt(std::pow(t_roomAPos.x - t_roomBPos.x, 2) + std::pow(t_roomAPos.y - t_roomBPos.y, 2));

		m_text.setString(std::to_string(cost));
	}
	bool operator>(const PointEdge& other)const
	{
		return cost > other.cost;
	}
	bool operator<(const PointEdge& other)const
	{
		return cost < other.cost;
	}
	bool operator==(const sf::Vector2f& other)
	{


		return (static_cast<sf::Vector2i>(m_roomAPos) == static_cast<sf::Vector2i>(other)) ||
			(static_cast<sf::Vector2i>(m_roomBPos) == static_cast<sf::Vector2i>(other));
	}
	bool operator==(const PointEdge& other) const
	{
		return (static_cast<sf::Vector2i>(m_roomAPos) == static_cast<sf::Vector2i>(other.m_roomAPos) &&
			static_cast<sf::Vector2i>(m_roomBPos) == static_cast<sf::Vector2i>(other.m_roomBPos)) ||
			(static_cast<sf::Vector2i>(m_roomAPos) == static_cast<sf::Vector2i>(other.m_roomBPos) &&
				static_cast<sf::Vector2i>(m_roomBPos) == static_cast<sf::Vector2i>(other.m_roomAPos));
	}

	void draw(sf::RenderWindow& t_window)
	{
		t_window.draw(visulisations);
		t_window.draw(m_text);
	}

	sf::Vector2f m_roomAPos;
	sf::Vector2f m_roomBPos;


	int m_roomAId = -1;
	int m_roomBId = -1;


	bool visited = false;
	sf::Text m_text;
	sf::Font* f;
	float cost = 0;
	sf::VertexArray visulisations;



};

class pQPointEdgeComparer
{
public:
	bool operator()(const PointEdge& a, const PointEdge& b) const {
		return a.cost > b.cost;
	}
};

class Triangle
{
public:

	Triangle() : visualiseation(sf::LineStrip) {}

	friend bool operator<(const Triangle& a, const Triangle& b)
	{
		return a.points[0].x < b.points[0].x;
	}


	friend bool operator>(const Triangle& a, const Triangle& b)
	{
		return a.points[0].x > b.points[0].x;
	}

	bool operator==(const Triangle& other)
	{
		int matchingPoints = 0;
		for (int i = 0; i < 3; i++)
		{
			if (isPartOfTriangle(other.points[i]))
			{
				matchingPoints++;
			}
		}

		if (matchingPoints == 3)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	void addPoint(int roomId, sf::Vector2f p)
	{

		if (size < 3)
		{
			roomIds.push_back(roomId);
			points.push_back(p);
			visualiseation.append(sf::Vertex(p, sf::Color::Red));
			size++;
			// triangle created
			if (size == 3)
			{
				visualiseation.append(sf::Vertex(points[0], sf::Color::Red));
				generateTriangleEdges();
			}
		}
	}

	void generateTriangleEdges()
	{
		edges.push_back(PointEdge(roomIds[0], points[0], roomIds[1], points[1]));
		edges.push_back(PointEdge(roomIds[1], points[1], roomIds[2], points[2]));
		edges.push_back(PointEdge(roomIds[2], points[2], roomIds[0], points[0]));
	}

	bool isPartOfTriangle(sf::Vector2f t_pos)
	{

		for (int i = 0; i < 3; i++)
		{
			if (static_cast<sf::Vector2i>(points[i]) == static_cast<sf::Vector2i>(t_pos))
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

	std::vector<int> roomIds;
	std::vector<sf::Vector2f> points;
	std::vector<PointEdge> edges;
};


class Point
{
public:
	Point() {};
	Point(sf::Vector2f t_position)
	{
		visual.setRadius(10);
		visual.setOrigin(10, 10);
		visual.setPosition(t_position);
		visual.setFillColor(sf::Color::Yellow);

		Loader* l = Loader::getInstance();
		f = l->loadFont("ASSETS/FONTS/nulshock.otf");

		m_text.setFont(*f);
		m_text.setFillColor(sf::Color::Black);
		m_text.setCharacterSize(100);
		m_text.setPosition(t_position);

	}
	bool hasTriangle(Triangle triange)
	{
		for (int i = 0; i < triangles.size(); i++)
		{
			if (triangles[i] == triange)
			{
				return true;
			}
		}
		return false;
	}


	bool visited = false;
	sf::CircleShape visual;
	std::vector<Triangle> triangles;
	std::vector<PointEdge> edges;

	sf::Text m_text;
	sf::Font* f;


};

class Room
{
	public:

		Room();

		Room(Grid t_grid);

		void projectOnGrid(Grid* t_backgroundGrid, sf::Vector2f t_mosuePosition);

		void cleanUpProjection();

		bool emplaceOnGrid(Grid* t_backgroundGrid, sf::Vector2f t_mosuePosition);

		void setPosition(sf::Vector2f t_mosuePosition);

		void draw(sf::RenderWindow& t_window);

		void scaleDown(float t_scaleValue);

		void rotate();

		void setWalkable();

		Cell* getCenterCell();

		Grid getGrid();

		void setColourOfOccupiedCells(sf::Color t_color);

		Cell* getClosestCellTo(sf::Vector2f t_position);

		Grid m_grid;

		int roomId = -1;

		Point point;

		std::queue<Cell*> projectedOn;

		std::vector<std::vector<Cell*>> cellsOccupied;

		
		
};

