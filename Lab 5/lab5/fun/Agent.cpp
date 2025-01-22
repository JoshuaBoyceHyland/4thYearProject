#include "Agent.h"

Agent::Agent(Grid* t_map, sf::Vector2f t_position) : m_map( t_map), m_position(t_position)
{

}

void Agent::update(float t_deltaTime)
{
    m_currentNode = m_map->cellSelection(m_position)->getNode();
  

 

    if (!m_currentPath.empty())
    {
        followPath();
    }
}



void Agent::followPath()
{

    if( VectorMath::vectorLength ( m_target->getPosition(), m_position  )  < 10);
    {
        m_currentPath.clear();
    }

    sf::Vector2f t_direction = VectorMath::directionVector(m_target->getPosition(), m_position);

    m_position += t_direction * 10.0f;
}

std::vector<Node*> Agent::pathFindTo(Node* t_goalNode)
{
    std::vector<Node*> path;
    m_map->resetGridCellForPathFinding(true, true);
    Search::breadhFirstGridCostAssignment(t_goalNode, t_goalNode->getPosition());
    m_map->resetGridCellForPathFinding(false, true);
    path = Search::AStar(m_currentNode);


    m_currentPath = path;

    m_target = m_currentPath.back();


    return path;
}
