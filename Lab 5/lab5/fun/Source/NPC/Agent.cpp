#include "NPC/Agent.h"

Agent::Agent(Grid* t_map, sf::Vector2f t_position) : m_map(t_map), m_position(t_position)
{
}

Agent::Agent(AgentUser* t_user, Grid* t_map, sf::Vector2f t_position) : m_user( t_user), m_map(t_map), m_position(t_position)
{

}

void Agent::update(float t_deltaTime)
{
    m_currentNode = m_map->cellSelection(m_position)->getNode();

    if (m_target != nullptr)
    {
        followPath(t_deltaTime);
    }
    else
    {
        m_direction = { 0, 0 };
    }
}



void Agent::followPath(float t_deltaTime)
{

    m_map->m_cells[m_target->m_row][m_target->m_column].setColor(sf::Color::Yellow);
    m_direction = VectorMath::directionVector( m_position, m_target->getPosition());

    m_position += m_direction * m_speed;


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
                m_hasTarget = false;
            }
            
            
            m_user->reachedTarget();
            
            
        }

    }

}

void Agent::reset()
{
    m_hasTarget = false;
    m_target = nullptr;
    m_currentPath.clear();
    //m_previousPath.
}

std::deque<Node*>Agent::pathFindTo(Node* t_goalNode)
{
    std::deque<Node*> path;

    if (m_currentNode == nullptr)
    {
        m_currentNode = m_map->cellSelection(m_position)->getNode();
    }

    m_hasTarget = true;
    
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
