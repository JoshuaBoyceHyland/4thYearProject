#pragma once
#include "Grid.h"
#include "Search.h"
#include "VectorMath.h"
class Agent
{
	public:

		Agent(Grid* t_map, sf::Vector2f t_position);

		void update(float t_deltaTime);

		void followPath(float t_deltaTime);

		float m_speed = 2.5;
		float m_rotation;
		sf::Vector2f m_position;

		std::queue<Node*> m_previousPath;
		std::deque<Node*> m_currentPath;
		std::deque<Node*> pathFindTo(Node* t_goalNode);

		Node* m_target = nullptr;
		Node* m_currentNode = nullptr;
		Grid* m_map = nullptr;
};

