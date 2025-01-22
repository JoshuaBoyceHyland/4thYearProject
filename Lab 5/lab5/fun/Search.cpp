#include "Search.h"

void Search::use()
{

}

std::vector<Node*> Search::breadhFirst(std::vector<Node*> t_neighbours, int& t_cost, sf::Vector2f t_goalPos)
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

std::vector<Node*> Search::AStar(Node* t_startNode)
{
	
	std::queue<Node*> expandedNodes;
	std::priority_queue<Node*, std::vector<Node*>, NodeComparision > nodePriorityQueue;

	t_startNode->setMarked(true);
	t_startNode->setBeingChecked(true);

	for (Node* node : t_startNode->getNeighbours())
	{
		std::cout<< "Checked Node: " << node->m_row << " " << node->m_column << std::endl;
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

	std::vector<Node*> path;

	if (!nodePriorityQueue.empty())
	{
		Node* pathSteps = nodePriorityQueue.top();

		while (pathSteps->previous != nullptr)
		{
			path.push_back(pathSteps);

			pathSteps = pathSteps->previous;
		}
		


	}

	
	return path;
}
