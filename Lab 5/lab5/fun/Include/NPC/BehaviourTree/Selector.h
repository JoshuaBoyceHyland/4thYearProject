#pragma once
#include <vector>
#include "BehaviourNode.h"
class Selector : public DecisionNode
{
	public:
		Selector(std::vector<std::unique_ptr<DecisionNode>>&& t_children) : m_decisions(std::move(t_children)){}
		
		DecisionNode* decide(float t_deltaTime) override
		{
			// trying all our decisions till one suceeds
			for (int i = 0; i < m_decisions.size(); i++)
			{
				DecisionNode* decision = m_decisions[i]->decide(t_deltaTime);

				// check sequences, if not failed then sequence condition passed and when further down that branch
				if (decision != nullptr)
				{
					return decision;
				}
					
			}

			return nullptr;
		}
	private:
		std::vector < std::unique_ptr<DecisionNode>> m_decisions;
};

