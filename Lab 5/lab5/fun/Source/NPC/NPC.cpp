#include "NPC/NPC.h"

NPC::NPC(Grid* t_map, BasePlayer* player, sf::Vector2f t_position) :
m_grid(t_map),
m_agent(t_map, t_position),
m_animator("ASSETS/IMAGES/NPC/1", m_body)
{
	m_tag = Enemy;
	setUpBehaviourTree(t_map);

	talking->m_player = player;
	m_agent.m_user = talking;
	talking->enter();
}


void NPC::update(float deltatime)
{
	

	//BehaviourNode* newDecision = m_behaviourTree->decide(deltatime);

	//if (newDecision != m_currentBehaviour)
	//{
	//	if (m_currentBehaviour)
	//	{
	//		m_currentBehaviour->onExit();
	//	}

	//	if (newDecision)
	//	{
	//		newDecision->onEnter();
	//	}

	//	m_currentBehaviour = newDecision;
	//	m_agent.m_user = m_currentBehaviour->getBehaviour();
	//}


	//if (m_currentBehaviour)
	//{
	//	m_currentBehaviour->preform(deltatime);
	//}

	talking->update(deltatime);

	m_animator.animate();


	m_body.setPosition(m_agent.m_position);

}

void NPC::draw(sf::RenderWindow& t_window)
{

	sf::CircleShape t;
	t.setRadius(10);
	t.setOrigin({ 5, 5 });
	t.setFillColor(sf::Color::Magenta);
	t.setPosition(m_agent.m_position);
	
	t_window.draw(m_body);
	t_window.draw(t);
}

void NPC::setUpBehaviourTree(Grid* t_map)
{

	Wander* wander = new Wander(t_map, &m_agent, &m_animator);
	talking = new Attack(t_map, &m_agent, &m_animator);

	NearPlayerCondition* nearPlayer = new NearPlayerCondition(std::bind(&NPC::closeToPlayer, this));

	WanderNode* wanderNode = new WanderNode(wander);
	AttackingNode* talkingNode = new AttackingNode(talking);

	//BehaviourNode* treeBase = std::make_unique < Selector>({
	//	new Sequence({nearPlayer, talkingNode}), wanderNode } 
	//
	//);

	// talk sequence
	//std::vector<std::unique_ptr<BehaviourNode>> talkSequenceChildren;
	//talkSequenceChildren.push_back(std::make_unique<NearPlayerCondition>(std::bind(&NPC::closeToPlayer, this)));
	////talkSequenceChildren.push_back(std::make_unique<TalkingNode>(talking));
	//std::unique_ptr<Sequence>  talkSequence = std::make_unique<Sequence>(std::move(talkSequenceChildren));

	//std::vector<std::unique_ptr<BehaviourNode>> selectorChildren;
	//selectorChildren.push_back(std::move(talkSequence));
	//selectorChildren.push_back(std::make_unique<WanderNode>(wander));

	//m_behaviourTree = std::make_unique<Selector>(std::move(selectorChildren));

	/*m_agent.m_user.push_back(wander);*/
}

bool NPC::closeToPlayer()
{

	Node* currentNode = m_grid->cellSelection(m_body.getPosition())->getNode();
	std::vector<Node*> neighbours = currentNode->getNeighbours();

	for (int i = 0; i < neighbours.size(); i++)
	{
		std::unordered_set<GameObject*> gameobjects =  m_grid->m_cells[neighbours[i]->m_row][neighbours[i]->m_column].getGameObjects();

		for (GameObject* gameobject : gameobjects)
		{
			if (gameobject->m_tag == Player)
			{
				if (gameobject->m_body.getPosition().x > m_body.getPosition().x)
				{
					m_body.setScale(1, 1);
				}
				else
				{
					m_body.setScale(-1, 1);
				}
				return true;
			}
		}
	}

	return false;
}


