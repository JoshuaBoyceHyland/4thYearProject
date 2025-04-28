#pragma once
#include "NPC/Talking.h"
#include "NPC/Wander.h"

enum class BehaviourState{ Failed, Running, Succeeded};


class BehaviourNode
{
	public:

		virtual BehaviourNode* update(float t_deltaTime)= 0;
        virtual void onEnter() {}
        virtual void preform(float t_deltaTime) {}
        virtual void onExit() {}
        virtual ~BehaviourNode() = default;
};


class WanderNode : public BehaviourNode {
public:
    WanderNode(Wander* wander) : m_wander(wander) {}

    BehaviourNode* update(float t_deltaTime) override {

        std::cout << "Wandering" << std::endl;
        return this;
    }

    void preform(float t_deltaTime) override
    {
        m_wander->update(t_deltaTime);
    }

private:
    Wander* m_wander;
};

class TalkingNode : public BehaviourNode {
public:
    TalkingNode(Talking* talking) : m_talking(talking){}

    BehaviourNode* update(float t_deltaTime) override {

        std::cout << "talking" << std::endl;
        return this;
    }

    void preform(float t_deltaTime) override
    {
        m_talking->update(t_deltaTime);
    }
private:
   Talking* m_talking;
};