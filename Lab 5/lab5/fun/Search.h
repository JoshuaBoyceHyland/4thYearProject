#pragma once
#include "Node.h"
#include <functional>
#include <queue>
#include "VectorMath.h"
#include <iostream>
class Search
{
	public:
		void use();

		static std::vector<Node*> breadhFirst(std::vector<Node*> t_neighbours, int& t_cost, sf::Vector2f t_goalPos);

		static std::vector<Node*>AStar (std::vector<Node*> t_neighbours);
};

