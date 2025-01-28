#include "NPC/BehaviourManagert.h"

BehaviourManager::BehaviourManager(Grid* t_grid, sf::Vector2f t_position) : m_grid( t_grid), m_agent( t_grid, t_position )
{
    m_currentBehaviour = new Wander(t_grid,&m_agent );
    m_currentType = BehaviourType::Wander;

    m_agent.m_user = m_currentBehaviour;
}

void BehaviourManager::update(float t_deltaTime)
{
    m_agent.update(t_deltaTime);
    m_currentBehaviour->update();
    
}

BehaviourType BehaviourManager::getCurrentBehaviourType()
{
    return m_currentType;
}
