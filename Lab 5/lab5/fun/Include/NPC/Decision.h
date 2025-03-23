#pragma once
#include "NPC.h"
#include "Wander.h"
class Decision
{
	public:
		Decision(Agent t_npc) : m_npc(t_npc) {};

		virtual bool condition() = 0;

		Agent m_npc;

		Decision* m_nextDecision = nullptr;
		Behaviour* m_behaviourAction = nullptr;

};


class WanderDecision : public Decision
{
	public:
		WanderDecision(Agent t_npc) : Decision(t_npc)
		{
			m_behaviourAction = new Wander(t_npc.m_map, &t_npc);
			
		};

		virtual bool condition() override
		{
			
			std::vector<int> itemsOfInterest = { 1 };

			return !itemsOfInterest.empty();

			
		};



};

