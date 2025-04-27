#pragma once
#include "BehaviourNode.h"
#include <functional>
class NearPlayerCondition : public BehaviourNode
{
	public:
		NearPlayerCondition(std::function<bool()> t_condition) :m_condition(t_condition) {}

	
		BehaviourState update(float t_deltaTime) override
		{
			if (m_condition())
			{
				return BehaviourState::Succeeded;
			}

			return BehaviourState::Failed;
		}

	private:
		std::function<bool()> m_condition;

		
};

