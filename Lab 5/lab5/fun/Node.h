#pragma once
#include <vector>
#include <SFML/Graphics.hpp>



class Node
{

	public:

		Node();
		Node(int t_row, int t_column, sf::Vector2f t_position) : m_row(t_row), m_column(t_column), m_position(t_position) {}

		

		void reset();

		void addNeighbour(Node* t_neighbour) { m_neighbours.push_back(t_neighbour); }


		void setMarked(bool t_marked) { m_marked = t_marked; }
		void setBeingChecked(bool t_beingChecked) { m_beingChecked = t_beingChecked; }
		void setCost(int t_cost) { m_cost = t_cost; };
		void setManhattan(int t_manhanttan) { m_euclidian = t_manhanttan; }
		void setEudclidian(float t_euclidian) { m_euclidian = t_euclidian; }
		void setHeuristic(float t_heuristic) { m_heuristic = t_heuristic; }

		bool isMarked() { return m_marked; }
		bool isBeingChecked() { return m_beingChecked; }

		int getCost() { return m_cost; };
		int getManhattan() { return m_manhanttan; }

		float getEudclidian() { return m_euclidian; }
		float getHeurisitic() { return m_heuristic; }

		sf::Vector2f getPosition() { return m_position; }

		std::vector<Node*> getNeighbours() { return m_neighbours; }

		int m_row = -1;
		int m_column = -1;
	private:
		sf::Vector2f m_position;

		float m_euclidian = -1;
		int m_manhanttan = -1;
		float m_heuristic = -1;
		int  m_cost = -1;

		bool m_marked = false;
		bool m_beingChecked = false;
		

		std::vector<Node*> m_neighbours;

};

struct NodeComparision {
	bool operator()(Node* const& n1, Node* const& n2)
	{
		return n1->getHeurisitic() < n2->getHeurisitic();
	}
};