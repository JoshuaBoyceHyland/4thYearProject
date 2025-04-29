#pragma once
#include "BehaviourNode.h"
#include <functional>


class Condition : public BehaviourNode
{
	public:
		Condition(std::function<bool()> t_condition) :m_condition(t_condition) {}

	
		BehaviourNode* decide(float t_deltaTime) override
		{
			if (m_condition())
			{
				return this;
			}

			return nullptr;
		}

	private:
		std::function<bool()> m_condition;

		
};

