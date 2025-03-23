#include "NPC/BehaviourManagert.h"

BehaviourManager::BehaviourManager(Grid* t_grid, sf::Vector2f t_position) : m_grid( t_grid), m_agent( t_grid, t_position )
{
    m_currentBehaviour = new Wander(t_grid,&m_agent );
    m_currentState = Wandering;

    m_agent.m_user = m_currentBehaviour;

    for (int i = 0; i < 1; i++)
    {
        decisionTree.push_back(new WanderDecision(m_agent));
    }
}

void BehaviourManager::update(float t_deltaTime)
{
    m_agent.update(t_deltaTime);
    m_currentBehaviour->update();


    
}

NPCState BehaviourManager::getCurrentBehaviourType()
{
    return m_currentState;
}
