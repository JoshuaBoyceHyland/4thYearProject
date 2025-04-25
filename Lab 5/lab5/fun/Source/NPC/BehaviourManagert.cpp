#include "NPC/BehaviourManagert.h"

BehaviourManager::BehaviourManager(Grid* t_grid, sf::Vector2f t_position) : m_grid( t_grid), m_agent( t_grid, t_position )
{
    


    Wander* wander = new Wander(t_grid, &m_agent);

    NearPlayerCondition* condition = new NearPlayerCondition(std::bind(&BehaviourManager::closeToPlayer, this));
   
    WanderNode* wanderNode = new WanderNode(wander);
    TalkingNode* talkingNode = new TalkingNode(wander);

    BehaviourNode* treeBase = new Selector({
        new Sequence({condition, talkingNode}),
        wanderNode
        });

    m_behaviourTree = treeBase;

    m_agent.m_user.push_back(wander);
    
}

void BehaviourManager::update(float t_deltaTime)
{
    m_agent.update(t_deltaTime);
    //m_currentBehaviour->update();
    
    if (m_behaviourTree)
    {
        m_behaviourTree->update();
    }
}

