#pragma once

#include "NPC/Behaviours/Attack.h"
#include "NPC/Behaviours/Talking.h"
#include "NPC/Behaviours/Wander.h"
#include "NPC/Behaviours/Death.h"
#include "NPC/Behaviours/Dash.h"


class DecisionNode
{
	public:

		virtual DecisionNode* decide(float t_deltaTime)= 0;
        virtual void onEnter() {}
        virtual void preform(float t_deltaTime) {}
        virtual void onExit() {}
        virtual Behaviour* getBehaviour() { return nullptr; };

        virtual ~DecisionNode() = default;
};


class WanderNode : public DecisionNode {
public:
    WanderNode(Wander* wander) : m_wander(wander) {}

    DecisionNode* decide(float t_deltaTime) override {

        //std::cout << "Wandering" << std::endl;
        return this;
    }

    void onEnter() override
    {
        m_wander->enter();
    }
    void preform(float t_deltaTime) override
    {
        m_wander->update(t_deltaTime);
    }

    void onExit() override
    {
        m_wander->reset();
    }
    virtual Behaviour* getBehaviour() override  { return m_wander; };
    private:
        Wander* m_wander;
};

class TalkingNode : public DecisionNode {
public:
    TalkingNode(Talking* talking) : m_talking(talking){}

    DecisionNode* decide(float t_deltaTime) override {

       // std::cout << "talking" << std::endl;
        return this;
    }
    void onEnter() override
    {

    }
    void preform(float t_deltaTime) override
    {
        m_talking->update(t_deltaTime);
    }

    void onExit() override
    {
       
    }
    virtual Behaviour* getBehaviour() override { return  m_talking; };

    private:
        Talking* m_talking;
};


class AttackingNode : public DecisionNode {
public:
    AttackingNode(Attack* t_attack) : m_attacking(t_attack) {}

    DecisionNode* decide(float t_deltaTime) override {

       // std::cout << "attacking" << std::endl;
        return this;
    }
    void onEnter() override
    {
        m_attacking->enter();
    }
    void preform(float t_deltaTime) override
    {
        m_attacking->update(t_deltaTime);
    }

    void onExit() override
    {
        m_attacking->exit();
    }
    virtual Behaviour* getBehaviour() override { return  m_attacking; };

private:
   Attack* m_attacking;
};

class DeathNode : public DecisionNode {
public:
    DeathNode(Death* t_dying) : m_dying(t_dying) {}

    DecisionNode* decide(float t_deltaTime) override {

        //std::cout << "Dying" << std::endl;
        return this;
    }
    void onEnter() override
    {
        m_dying->startDeath();
    }
    void preform(float t_deltaTime) override
    {
        
        m_dying->update(t_deltaTime);
    }

    void onExit() override
    {
      
    }
    virtual Behaviour* getBehaviour() override { return  m_dying; };

private:
    Death* m_dying;
};


class DashNode : public DecisionNode {
public:
    DashNode(Dash* t_dying) : m_dash(t_dying) {}

    DecisionNode* decide(float t_deltaTime) override {

      //  std::cout << "Dashing" << std::endl;
        return this;
    }
    void onEnter() override
    {
        m_dash->startDash();
    }
    void preform(float t_deltaTime) override
    {

        m_dash->update(t_deltaTime);
    }

    void onExit() override
    {
        m_dash->endDash();
    }
    virtual Behaviour* getBehaviour() override { return  m_dash; };

private:
    Dash* m_dash;
};


class EmptyNode : public DecisionNode {
public:
    EmptyNode() {}

    DecisionNode* decide(float t_deltaTime) override {

       // std::cout << "Emptu" << std::endl;
        return this;
    }
    void onEnter() override
    {

    }
    void preform(float t_deltaTime) override
    {


    }

    void onExit() override
    {

    }
    virtual Behaviour* getBehaviour() override { return  nullptr; };

private:

};