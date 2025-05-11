#pragma once
#include "GameObject.h"
#include "Actors/Animator.h"
#include "Behaviours/Attack.h"
#include "Behaviours/Death.h"
#include "BehaviourTree/ConditionNodes.h"
#include "BehaviourTree/Selector.h"
#include "BehaviourTree/Sequence.h"
#include "BehaviourTree/BehaviourNode.h"
class NPC : public GameObject
{

	public:
		NPC(Grid* t_map,  BasePlayer* player, sf::Vector2f t_position= {-500, -500}, Tag t_tag = Enemy, std::string t_texturePath = "1", sf::Vector2f t_spriteOrigin = {20, 100});

		void update(float deltatime);

		void draw(sf::RenderWindow& t_window);

		void setUpBehaviourTree(Grid* t_map, BasePlayer* t_player);

		void collisionWith(Tag t_tag) override;

	private:
		
		bool bulletDetected();

		bool closeToPlayer();

		bool attackPlayer();

		bool dead();


		Dash* m_dashBehaviour = nullptr;
		Grid* m_grid;
		Agent m_agent;
		Animator m_animator;
		DecisionNode* m_currentBehaviour = nullptr;
		std::unique_ptr<DecisionNode> m_behaviourTree;
		float m_health = 100;

		bool m_startedAttacking = false;
		bool m_startDashing = false;
		bool m_dashed = false;
};

