#pragma once
#include "World/Grid.h"
#include "World/Search.h"
#include "Utility/VectorMath.h"
#include "AgentUser.h"

class Agent
{
	public:

		Agent( Grid* t_map, sf::Vector2f t_position);
		Agent(AgentUser* t_user, Grid* t_map, sf::Vector2f t_position);

		void update(float t_deltaTime);

		void followPath(float t_deltaTime);


		std::deque<Node*> pathFindTo(Node* t_goalNode);

		AgentUser* m_user = nullptr;

		float m_speed = 2.5;
		float m_rotation;
		sf::Vector2f m_position;

		std::queue<Node*> m_previousPath;
		std::deque<Node*> m_currentPath;
		
		sf::Vector2f m_direction = { 0,0 };
		bool m_hasTarget = false;
		Node* m_target = nullptr;
		Node* m_currentNode = nullptr;
		Grid* m_map = nullptr;

		
};

