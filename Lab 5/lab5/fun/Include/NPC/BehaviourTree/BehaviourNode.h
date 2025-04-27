#pragma once
#include "NPC/Talking.h"
#include "NPC/Wander.h"

enum class BehaviourState{ Failed, Running, Succeeded};


class BehaviourNode
{
	public:
		virtual BehaviourState update(float t_deltaTime) = 0;
};


class WanderNode : public BehaviourNode {
public:
    WanderNode(Wander* wander) : m_wander(wander) {}

    BehaviourState update(float t_deltaTime) override {

        std::cout << "Wandering" << std::endl;
        m_wander->update(t_deltaTime);
        return BehaviourState::Running;
    }

private:
    Wander* m_wander;
};

class TalkingNode : public BehaviourNode {
public:
    TalkingNode(Talking* talking) : m_talking(talking){}

    BehaviourState update(float t_deltaTime) override {

        std::cout << "talking" << std::endl;
        m_talking->update(t_deltaTime);
        return BehaviourState::Succeeded;
    }

private:
   Talking* m_talking;
};