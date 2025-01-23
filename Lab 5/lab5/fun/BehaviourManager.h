#pragma once
#include "Node.h"


class Action
{
	public:

		Node* m_goalNode;

};

class Behaviour
{
	public:
		virtual Action* getAction() = 0;
};


class Wander : public Behaviour
{



};

class BehaviourManager
{

	public:


	private:


		Behaviour* m_currentBehaviour;

};

