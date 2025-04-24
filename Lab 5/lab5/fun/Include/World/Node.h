#pragma once
#include <vector>
#include <SFML/Graphics.hpp>



enum class Direction {
	Top = 0,
	TopRight = 1,
	Right = 2,
	BottomRight = 3,
	Bottom = 4,
	BottomLeft = 5,
	Left = 6,
	TopLeft = 7
};


class Node
{

	public:
	public:
		Node(int t_row, int t_column, sf::Vector2f t_position) : m_row(t_row), m_column(t_column), m_position(t_position) {}

		void resetCosts();

		void resetMarkings();

		void clearNeighbours() { m_neighbours.clear(); }
		void addNeighbour(Node* t_neighbour) { m_neighbours.push_back(t_neighbour); }
		void addNeighbourDirection(Direction t_direction) { m_neighbourDirections.push_back(t_direction); }

		void setMarked(bool t_marked) { m_marked = t_marked; }
		void setBeingChecked(bool t_beingChecked) { m_beingChecked = t_beingChecked; }
		void setCost(int t_cost) { m_cost = t_cost; };
		void setManhattan(int t_manhanttan) { m_manhanttan = t_manhanttan; }
		void setEudclidian(float t_euclidian) { m_euclidian = t_euclidian; }
		void setHeuristic(float t_heuristic) { m_heuristic = t_heuristic; }
		void setPosition(sf::Vector2f t_position) { m_position = t_position; }

		bool isMarked() { return m_marked; }
		bool isBeingChecked() { return m_beingChecked; }

		bool isWallNode();

		int getCost() { return m_cost; };
		int getManhattan() { return m_manhanttan; }

		int getEudclidian() { return m_euclidian; }
		int getHeurisitic() { return m_heuristic; }

		sf::Vector2f getPosition() { return m_position; }

		std::vector<Node*> getNeighbours() { return m_neighbours; }

		sf::Vector2i m_direction = { 0,0 };
		Node* previous = nullptr;
		int m_row = -1;
		int m_column = -1;
	private:
		sf::Vector2f m_position;

		int m_euclidian = -1;
		int m_manhanttan = -1;
		int m_heuristic = -1;

		int  m_cost = -1;

		bool m_marked = false;
		bool m_beingChecked = false;
		
		std::vector<Direction> m_neighbourDirections;
		std::vector<Node*> m_neighbours;

};

struct NodeComparision {
	bool operator()(Node* const& n1, Node* const& n2)
	{
		return n1->getHeurisitic() > n2->getHeurisitic();
	}
};