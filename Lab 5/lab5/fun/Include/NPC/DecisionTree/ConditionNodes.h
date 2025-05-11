#pragma once
#include "DecisonNode.h"
#include <functional>

/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class Condition : public DecisionNode
{
	public:
		Condition(std::function<bool()> t_condition) :m_condition(t_condition) {}

	
		DecisionNode* decide(float t_deltaTime) override
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

