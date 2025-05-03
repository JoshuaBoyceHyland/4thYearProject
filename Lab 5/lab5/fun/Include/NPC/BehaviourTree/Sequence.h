#pragma once
#include "BehaviourNode.h"
class Sequence : public BehaviourNode
{
	public:
		Sequence(std::vector<std::unique_ptr<BehaviourNode>>&& t_children) : m_children(std::move(t_children)) {}
		
		BehaviourNode* decide(float t_deltaTime) override
		{
			BehaviourNode* finalDecicion = nullptr;
			for (int i = 0; i < m_children.size(); i++)
			{
				// check condition if condition is true
				// if true it will coninue onto next loop which bring us to next node
				BehaviourNode* decision = m_children[i]->decide(t_deltaTime);

				// if condition failed then we want to return and go down different branch
				if (decision == nullptr)
				{
					return nullptr;
				}
				else
				{

					finalDecicion = decision;
				}
			}

			return finalDecicion;
		}
	private:
		std::vector<std::unique_ptr<BehaviourNode>> m_children;

	
};

