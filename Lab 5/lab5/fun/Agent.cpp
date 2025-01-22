#include "Agent.h"

std::vector<Node*> Agent::pathFindTo(Node* t_goalNode, Grid* t_grid)
{
    std::vector<Node*> path;
    t_grid->resetGridCellForPathFinding(true, true);
    Search::breadhFirstGridCostAssignment(t_goalNode, t_goalNode->getPosition());
    t_grid->resetGridCellForPathFinding(false, true);
    path = Search::AStar(m_currentNode);
    return path;
}
