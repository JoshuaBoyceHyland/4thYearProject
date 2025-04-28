#include "World/Search.h"

void Search::use()
{

}

std::vector<Node*> Search::breadhFirstGridCostAssignment(Node* t_goalNode, sf::Vector2f t_goalPos)
{
	int cost = 0;
	std::vector<Node*> nextNeighbours;
	std::vector<Node*> currentNeightbours = t_goalNode->getNeighbours();

	// setu up the goal node to be 0 before entering loop 
	t_goalNode->setManhattan(cost);
	t_goalNode->setEudclidian(cost);
	t_goalNode->setHeuristic(cost);
	t_goalNode->setMarked(true);

	// while we still have nodes to go through
	while (!currentNeightbours.empty())
	{

		cost++;

		for (int i = 0; i < currentNeightbours.size(); i++)
		{
			// if marked or goal dont set cost
			if (!currentNeightbours[i]->isMarked() && currentNeightbours[i]->getManhattan() != 0)
			{
				currentNeightbours[i]->setManhattan(cost);
				currentNeightbours[i]->setEudclidian(VectorMath::vectorLength(t_goalPos, currentNeightbours[i]->getPosition()));
				currentNeightbours[i]->setHeuristic(cost + currentNeightbours[i]->getEudclidian());
				currentNeightbours[i]->setMarked(true);
			}

			for (int k = 0; k < currentNeightbours[i]->getNeighbours().size(); k++)
			{
				if (!currentNeightbours[i]->getNeighbours()[k]->isMarked() && !currentNeightbours[i]->getNeighbours()[k]->isBeingChecked())
				{
					currentNeightbours[i]->getNeighbours()[k]->setBeingChecked(true);
					nextNeighbours.push_back(currentNeightbours[i]->getNeighbours()[k]);
				}

			}

		}

		
		currentNeightbours = nextNeighbours;
		nextNeighbours.clear();
	}
	


	return nextNeighbours;
}

std::vector<Node*> Search::breadhFirstCostAssignmentIncremental(std::vector<Node*> t_neighbours, int& t_cost, sf::Vector2f t_goalPos)
{
	std::vector<Node*> nextNeighbours;

	t_cost++;
	for (int i = 0; i < t_neighbours.size(); i++)
	{
		// if marked or goal dont set cost
		if (!t_neighbours[i]->isMarked() && t_neighbours[i]->getManhattan() != 0)
		{
			t_neighbours[i]->setManhattan(t_cost);
			t_neighbours[i]->setEudclidian(VectorMath::vectorLength(t_goalPos, t_neighbours[i]->getPosition()));
			t_neighbours[i]->setHeuristic(t_cost + t_neighbours[i]->getEudclidian());
			t_neighbours[i]->setMarked(true);
		}

		for (int k = 0; k < t_neighbours[i]->getNeighbours().size(); k++)
		{
			if (!t_neighbours[i]->getNeighbours()[k]->isMarked() && !t_neighbours[i]->getNeighbours()[k]->isBeingChecked())
			{
				t_neighbours[i]->getNeighbours()[k]->setBeingChecked( true);
				nextNeighbours.push_back(t_neighbours[i]->getNeighbours()[k]);
			}

		}

	}


    return  nextNeighbours;
}

std::vector<Node*> Search::breadhFirstIncrementalGoal(std::vector<Node*> t_neighbours, sf::Vector2f t_goalPos)
{
	std::vector<Node*> nextNeighbours;

	for (int i = 0; i < t_neighbours.size(); i++)
	{
		// if marked or goal dont set cost
		if (!t_neighbours[i]->isMarked() && t_neighbours[i]->getManhattan() != 0)
		{
			t_neighbours[i]->setMarked(true);
		}

		for (int k = 0; k < t_neighbours[i]->getNeighbours().size(); k++)
		{
			if (!t_neighbours[i]->getNeighbours()[k]->isMarked() && !t_neighbours[i]->getNeighbours()[k]->isBeingChecked())
			{
				t_neighbours[i]->getNeighbours()[k]->setBeingChecked(true);
				nextNeighbours.push_back(t_neighbours[i]->getNeighbours()[k]);
			}

		}

	}

	return  nextNeighbours;
}

std::deque<Node*>Search::AStar(Node* t_startNode)
{
	
	std::queue<Node*> expandedNodes;
	std::priority_queue<Node*, std::vector<Node*>, NodeComparision > nodePriorityQueue;

	t_startNode->setMarked(true);
	t_startNode->setBeingChecked(true);

	for (Node* node : t_startNode->getNeighbours())
	{
		//std::cout<< "Checked Node: " << node->m_row << " " << node->m_column << std::endl;
		node->previous=t_startNode;
		node->setBeingChecked(true);
		nodePriorityQueue.push(node);
	}
	
	while (!nodePriorityQueue.empty())
	{
		if (nodePriorityQueue.top()->getHeurisitic() == 0)
		{
			break;
		}

		expandedNodes.push(nodePriorityQueue.top());
		expandedNodes.back()->setMarked(true);
		nodePriorityQueue.pop();

		//std::cout << "Expanded Node: " << expandedNodes.back()->m_row << " " << expandedNodes.back()->m_column << std::endl;

		for (Node* node : expandedNodes.back()->getNeighbours())
		{
			// we dont want to add the node if its already been expanded or is in the queue to be expanded
			if (!node->isMarked() && !node->isBeingChecked())
			{
				node->previous = expandedNodes.back();
				node->setBeingChecked(true);
				nodePriorityQueue.push(node);

				//std::cout << "Checked Node: " << node->m_row << " " << node->m_column << std::endl;
			}
		}

		
	}

	std::deque<Node*> path;

	if (!nodePriorityQueue.empty())
	{
		Node* pathSteps = nodePriorityQueue.top();

		while (pathSteps->previous != nullptr)
		{
			path.push_front(pathSteps);

			pathSteps = pathSteps->previous;
		}


	}

	
	return path;
}

std::deque<Node*> Search::AStarDirectionBased(Node* t_startNode, sf::Vector2i t_startDirection)
{

	std::queue<Node*> expandedNodes;
	std::priority_queue<Node*, std::vector<Node*>, NodeComparision > nodePriorityQueue;

	t_startNode->setMarked(true);
	t_startNode->setBeingChecked(true);
	t_startNode->m_direction = { 0,0 };

	for (Node* node : t_startNode->getNeighbours())
	{

		std::cout << "Checked Node: " << node->m_row << " " << node->m_column << std::endl;
		
		sf::Vector2i startDirection = static_cast<sf::Vector2i>(node->getPosition() - t_startNode->getPosition());
		if (startDirection.x != 0) { startDirection.x /= std::abs(startDirection.x); }
		if (startDirection.y != 0) { startDirection.y /= std::abs(startDirection.y); }
		node->m_direction = startDirection;

		node->previous = t_startNode;
		node->setBeingChecked(true);

		

		nodePriorityQueue.push(node);
	}

	while (!nodePriorityQueue.empty())
	{
		if (nodePriorityQueue.top()->getHeurisitic() == 0)
		{
			break;
		}

		expandedNodes.push(nodePriorityQueue.top());
		expandedNodes.back()->setMarked(true);
		nodePriorityQueue.pop();

		std::cout << "Expanded Node: " << expandedNodes.back()->m_row << " " << expandedNodes.back()->m_column << std::endl;

		for (Node* node : expandedNodes.back()->getNeighbours())
		{
			// we dont want to add the node if its already been expanded or is in the queue to be expanded
			if (!node->isMarked() && !node->isBeingChecked())
			{
				node->previous = expandedNodes.back();
				node->setBeingChecked(true);
				nodePriorityQueue.push(node);

				std::cout << "Checked Node: " << node->m_row << " " << node->m_column << std::endl;
			}
		}


	}

	std::deque<Node*> path;

	if (!nodePriorityQueue.empty())
	{
		Node* pathSteps = nodePriorityQueue.top();

		while (pathSteps->previous != nullptr)
		{
			path.push_front(pathSteps);

			pathSteps = pathSteps->previous;
		}


	}


	return path;
}

void Search::nodeReset(std::vector<Node*> t_visitedNodes)
{

	for (Node* node : t_visitedNodes)
	{
		node->resetMarkings();
	}
}
