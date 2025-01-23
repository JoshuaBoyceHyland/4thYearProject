#include "Agent.h"

Agent::Agent(Grid* t_map, sf::Vector2f t_position) : m_map(t_map), m_position(t_position)
{

}

void Agent::update(float t_deltaTime)
{
    m_currentNode = m_map->cellSelection(m_position)->getNode();

    if (m_target != nullptr)
    {
        followPath(t_deltaTime);
    }
}



void Agent::followPath(float t_deltaTime)
{

    m_map->m_cells[m_target->m_row][m_target->m_column].setColor(sf::Color::Yellow);
    sf::Vector2f t_direction = VectorMath::directionVector( m_position, m_target->getPosition());

    m_position += t_direction * m_speed;


    if (VectorMath::vectorLength(m_position, m_target->getPosition()) < 2.5)
    {
        if (!m_currentPath.empty())
        {
            m_previousPath.push(m_target);
            m_target = m_currentPath.front();
            m_currentPath.pop_front();
            

        }
        else
        {
            m_previousPath.push(m_target);
            m_target = nullptr;
            
            while (!m_previousPath.empty())
            {
                m_map->m_cells[m_previousPath.front()->m_row][m_previousPath.front()->m_column].setColor(sf::Color::White);
                m_previousPath.pop();
            }
        }

    }

}

std::deque<Node*>Agent::pathFindTo(Node* t_goalNode)
{
    
    std::deque<Node*> path;
    m_map->resetGridCellForPathFinding(true, true);
    Search::breadhFirstGridCostAssignment(t_goalNode, t_goalNode->getPosition());
    
    // visual rep
    m_map->resetGridCellForPathFinding(false, true);
    path = Search::AStar(m_currentNode);

    // path finding
    m_map->resetGridCellForPathFinding(false, true);
    m_currentPath = Search::AStar(m_currentNode);

    m_target = m_currentPath.front();
    m_currentPath.pop_front();

    while (!path.empty())
    {
        m_map->m_cells[path.front()->m_row][path.front()->m_column].setColor(sf::Color::Green);
        path.pop_front();
    }


    return path;
}
