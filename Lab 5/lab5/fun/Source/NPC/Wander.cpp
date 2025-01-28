#include "NPC/Wander.h"

Wander::Wander(Grid* t_grid, Agent* t_agent) : Behaviour( t_grid, t_agent)
{

    m_agent->pathFindTo(getRandomNode());

}

void Wander::update()
{

    if (timeToFindNewTarget())
    {
        m_agent->pathFindTo(getRandomNode());  
    }
    
   
}

void Wander::reachedTarget()
{
    std::cout<< "Reached target" << std::endl;
    
    m_timer.restart();
    m_targetWaitingTime = rand() % 15;
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