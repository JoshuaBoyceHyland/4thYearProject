#include "NPC/NPC.h"

NPC::NPC(Grid* t_map, BasePlayer* player, sf::Vector2f t_position) :
m_grid(t_map),
m_agent(t_map, t_position),
m_animator("ASSETS/IMAGES/NPC/1", { "/Idle", "/Run", "/Dead"}, m_body, {20.0f, 56.0f})
{
	m_tag = Enemy;
	setUpBehaviourTree(t_map, player);

}


void NPC::update(float deltatime)
{
	

	BehaviourNode* newDecision = m_behaviourTree->decide(deltatime);

	if (newDecision != m_currentBehaviour)
	{
		if (m_currentBehaviour)
		{
			m_currentBehaviour->onExit();
		}

		if (newDecision)
		{
			newDecision->onEnter();
		}

		m_currentBehaviour = newDecision;
		m_agent.m_user = m_currentBehaviour->getBehaviour();
	}


	if (m_currentBehaviour)
	{
		m_currentBehaviour->preform(deltatime);
	}


	

	Cell* previousCell = m_grid->cellSelection(m_body.getPosition());

	previousCell->removeGameObject(this);

	m_body.setPosition(m_agent.m_position);

	Cell* currentCell = m_grid->cellSelection(m_body.getPosition());

	currentCell->addToGameObjects(this);
}

void NPC::draw(sf::RenderWindow& t_window)
{

	sf::CircleShape t;
	t.setRadius(10);
	t.setOrigin({ 5, 5 });
	t.setFillColor(sf::Color::Magenta);
	t.setPosition(m_agent.m_position);
	t_window.draw(t);
	t_window.draw(m_body);
	if (m_currentBehaviour)
	{
		m_currentBehaviour->getBehaviour()->draw(t_window);
	}
	 // most behaviours dont need to draw 
	
}

void NPC::setUpBehaviourTree(Grid* t_map, BasePlayer* t_player)
{

	Wander* wander = new Wander(t_map, &m_agent, &m_animator);
	Death* death = new Death(t_map, &m_agent, &m_animator);

	Talking* talk = new Talking(t_map, &m_agent, &m_animator);
	Attack* attack = new Attack(t_map, &m_agent, &m_animator);
	attack->m_player = t_player;


	std::vector<std::unique_ptr<BehaviourNode>> deathSequenceChildren;
	deathSequenceChildren.push_back(std::make_unique<Condition>(std::bind(&NPC::dead, this)));
	deathSequenceChildren.push_back(std::make_unique<DeathNode>(death));
	std::unique_ptr<Sequence> deathSequence = std::make_unique<Sequence>(std::move(deathSequenceChildren));


	std::vector<std::unique_ptr<BehaviourNode>> attackSequenceChildren;
	attackSequenceChildren.push_back(std::make_unique<Condition>(std::bind(&NPC::attackPlayer, this)));
	attackSequenceChildren.push_back(std::make_unique<AttackingNode>(attack));
	std::unique_ptr<Sequence>  attackSequence = std::make_unique<Sequence>(std::move(attackSequenceChildren));

	std::vector<std::unique_ptr<BehaviourNode>> selectorChildren;

	selectorChildren.push_back(std::move(deathSequence)); //  check if dead
	selectorChildren.push_back(std::move(attackSequence)); // check if in attacking range
	selectorChildren.push_back(std::make_unique<WanderNode>(wander)); // else wander

	m_behaviourTree = std::make_unique<Selector>(std::move(selectorChildren));

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

bool NPC::attackPlayer()
{

	if (!m_startedAttacking)
	{
		Node* currentNode = m_grid->cellSelection(m_body.getPosition())->getNode();
		std::vector<Node*> neighbours = currentNode->getNeighbours();

		for (int i = 0; i < neighbours.size(); i++)
		{
			std::unordered_set<GameObject*> gameobjects = m_grid->m_cells[neighbours[i]->m_row][neighbours[i]->m_column].getGameObjects();

			for (GameObject* gameobject : gameobjects)
			{
				if (gameobject->m_tag == Player)
				{
					m_startedAttacking = true;
					return true;
				}
			}
		}
	}
	

	return m_startedAttacking;
}

void NPC::collisionWith(Tag t_tag)
{

	if (t_tag == Bullet_Player)
	{
		m_health -= 100;
	}
}


