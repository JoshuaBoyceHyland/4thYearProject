#pragma once
#include <vector>
#include "BehaviourNode.h"
class Selector : public BehaviourNode
{
	public:
		Selector(std::vector<std::unique_ptr<BehaviourNode>>&& t_children) : m_decisions(std::move(t_children)){}
		
		BehaviourNode* decide(float t_deltaTime) override
		{
			// trying all our decisions till one suceeds
			for (int i = 0; i < m_decisions.size(); i++)
			{
				BehaviourNode* decision = m_decisions[i]->decide(t_deltaTime);

				// check sequences, if not failed then sequence condition passed and when further down that branch
				if (decision != nullptr)
				{
					return decision;
				}
					
			}

			return nullptr;
		}
	private:
		std::vector < std::unique_ptr<BehaviourNode>> m_decisions;
};

