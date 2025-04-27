#pragma once
#include "BehaviourNode.h"
class Sequence : public BehaviourNode
{
	public:
		Sequence(const std::vector<BehaviourNode*>& t_children) : m_children(t_children) {}
		
		BehaviourState update(float t_deltaTime) override
		{
			for (int i = 0; i < m_children.size(); i++)
			{
				BehaviourState currentState = m_children[i]->update(t_deltaTime);
				if (currentState != BehaviourState::Succeeded)
				{
					return currentState;
				}
			}

			return BehaviourState::Succeeded;
		}
	private:
		std::vector<BehaviourNode*> m_children;

		
};

