#include "NPC/Wander.h"

Wander::Wander(Grid* t_grid, Agent* t_agent, Animator* t_animator) : Behaviour( t_grid, t_agent, t_animator)
{

   

}

void Wander::update(float t_deltaTime)
{

    if (timeToFindNewTarget())
    {
        m_agent->pathFindTo(getRandomNode());  
    }

    m_agent->update(t_deltaTime);

    if (m_agent->m_direction.x != 0)
    {
        if (m_agent->m_direction.x > 0)
        {
            m_animator->m_sprite.setScale(1, 1);
        }
        else
        {
            m_animator->m_sprite.setScale(-1, 1);
        }
    }
   
    // if we are stopping for moment after reaching desitination
    if (m_agent->m_direction.x == 0 && m_agent->m_direction.y == 0)
    {
        m_animator->m_currentState = 0;
    }
    else
    {
        m_animator->m_currentState = 1;
        m_animator->animate();
    }
}

void Wander::reachedTarget()
{
    std::cout<< "Reached target" << std::endl;
    
    m_timer.restart();
    m_targetWaitingTime = rand() % 15;
}

void Wander::enter()
{
    if (previousTarget != nullptr)
    {
        m_agent->pathFindTo(previousTarget);
    }
}

void Wander::reset()
{
    if (!m_agent->m_currentPath.empty())
    {
        previousTarget = m_agent->m_currentPath.back();
    }
    
    m_agent->reset();
}


Node* Wander::getRandomNode()
{

    // get random spot on map
    std::vector<Cell*> traversal = m_grid->m_traversableCells;

    int maxCells = traversal.size();


    int randCell = rand() % maxCells;

    return traversal[randCell]->getNode();
}

bool Wander::timeToFindNewTarget()
{

    if (!m_agent->m_hasTarget)
    {
        float timeWaiting = m_timer.getElapsedTime().asSeconds();

        if (timeWaiting > m_targetWaitingTime)
        {
            return true;
        }
    }

    return false;
}

void Wander::draw(sf::RenderWindow& t_window)
{
}
