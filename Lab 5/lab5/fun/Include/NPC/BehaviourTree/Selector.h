#pragma once
#include <vector>
#include "BehaviourNode.h"
class Selector : public BehaviourNode
{
	public:
		Selector(std::vector<BehaviourNode*> t_children) : m_decisions(t_children){}
		
		BehaviourState update() override 
		{
			// trying all our decisions till one suceeds
			for (int i = 0; i < m_decisions.size(); i++)
			{
				if (m_decisions[i]->update() != BehaviourState::Failed)
				{
					return BehaviourState::Succeeded;
				}
					
			}

			return BehaviourState::Failed;
		}
	private:
		std::vector<BehaviourNode*> m_decisions;
};

