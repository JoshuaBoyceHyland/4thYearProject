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
		if (!t_neighbours[i]->isMarked() && t_neighbours[i]->getCost() != 0)
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

std::priority_queue<Node*, std::vector<Node*>, NodeComparision > Search::AStar(std::vector<Node*> t_neighbours, int& t_cost)
{

	std::priority_queue<Node*, std::vector<Node*>, NodeComparision > pR;

	for (int i = 0; i < t_neighbours.size(); i++)
	{
		pR.push(t_neighbours[i]);
	}
	
	while (!pR.empty())
	{
		std::cout << pR.top()->getHeurisitic() << std::endl;

		pR.pop();
	}

	return pR;
}
