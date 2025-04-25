#pragma once

#include "NPC/Wander.h"

enum class BehaviourState{ Failed, Running, Succeeded};


class BehaviourNode
{
	public:
		virtual BehaviourState update() = 0;
};


class WanderNode : public BehaviourNode {
public:
    WanderNode(Wander* wander) : m_wander(wander) {}

    BehaviourState update() override {

        std::cout << "Wandering" << std::endl;
        m_wander->update();
        return BehaviourState::Running;
    }

private:
    Wander* m_wander;
};

class TalkingNode : public BehaviourNode {
public:
    TalkingNode(Wander* wander) : m_wander(wander) {}

    BehaviourState update() override {

        std::cout << "talking" << std::endl;
        m_wander->update();
        return BehaviourState::Running;
    }

private:
    Wander* m_wander;
};