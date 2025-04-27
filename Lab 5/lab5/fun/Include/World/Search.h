#pragma once
#include "Node.h"
#include <functional>
#include <queue>
#include "Utility/VectorMath.h"
#include <iostream>
class Search
{
	public:
		void use();

		

		static std::vector<Node*> breadhFirstGridCostAssignment(Node* t_goalNode, sf::Vector2f t_goalPos);
		static std::vector<Node*> breadhFirstCostAssignmentIncremental(std::vector<Node*> t_neighbours, int& t_cost, sf::Vector2f t_goalPos);
		static std::vector<Node*> breadhFirstIncrementalGoal(std::vector<Node*> t_neighbours, sf::Vector2f t_goalPos);

		static std::deque<Node*> AStar (Node* t_startNode);

		static std::deque<Node*> AStarDirectionBased(Node* t_startNode, sf::Vector2i t_startDirection);

		static void nodeReset(std::vector<Node*> t_visitedNodes);
};

