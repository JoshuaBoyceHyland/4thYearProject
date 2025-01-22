#pragma once
#include "Grid.h"
#include "Search.h"

class Agent
{
	public:

		
		std::vector<Node*> pathFindTo(Node* t_goalNode, Grid* t_grid);

	private:

		Node* m_currentNode = nullptr;
};

