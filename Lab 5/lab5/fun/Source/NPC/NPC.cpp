#include "NPC/NPC.h"

NPC::NPC(Grid* t_map, BasePlayer* player, sf::Vector2f t_position, Tag t_tag, std::string t_texturePath, sf::Vector2f t_spriteOrigin) :
m_grid(t_map),
m_agent(t_map, t_position),
m_animator("ASSETS/IMAGES/NPC/" + t_texturePath, { "/Idle", "/Run", "/Death", "/Dash"}, m_body, t_spriteOrigin)
{
	m_tag = t_tag;
	setUpBehaviourTree(t_map, player);
	m_body.setPosition(m_agent.m_position);

}


void NPC::update(float deltatime)
{
	

	DecisionNode* newDecision = m_behaviourTree->decide(deltatime);

	if ( newDecision && newDecision != m_currentBehaviour )
	{
		if (m_currentBehaviour)
		{
			m_currentBehaviour->onExit();
		}

		if (newDecision)
		{
			m_agent.m_user = newDecision->getBehaviour();
			newDecision->onEnter();
		}

		m_currentBehaviour = newDecision;
		
	}


	if (m_currentBehaviour->getBehaviour() != nullptr)
	{
		m_currentBehaviour->preform(deltatime);
	}
	else
	{
		m_animator.m_currentState = 0;
		m_animator.animate();
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
	//t_window.draw(t);
	t_window.draw(m_body);
	if (m_currentBehaviour)
	{
		if (m_currentBehaviour->getBehaviour())
		{
			m_currentBehaviour->getBehaviour()->draw(t_window);
		}
		
	}
	 // most behaviours dont need to draw 
	
}

void NPC::setUpBehaviourTree(Grid* t_map, BasePlayer* t_player)
{
	std::vector<std::unique_ptr<DecisionNode>> selectorChildren;
	Wander* wander = new Wander(t_map, &m_agent, &m_animator);
	if (m_tag == Enemy)
	{
		Death* death = new Death(t_map, &m_agent, &m_animator);

		Talking* talk = new Talking(t_map, &m_agent, &m_animator);
		m_dashBehaviour = new Dash(t_map, &m_agent, &m_animator, m_startDashing);
		Attack* attack = new Attack(t_map, &m_agent, &m_animator);
		attack->m_player = t_player;

		// dead die
		std::vector<std::unique_ptr<DecisionNode>> deathSequenceChildren;
		deathSequenceChildren.push_back(std::make_unique<Condition>(std::bind(&NPC::dead, this)));
		deathSequenceChildren.push_back(std::make_unique<DeathNode>(death));
		std::unique_ptr<Sequence> deathSequence = std::make_unique<Sequence>(std::move(deathSequenceChildren));

		//
		std::vector<std::unique_ptr<DecisionNode>> dashSequenceChildren;
		dashSequenceChildren.push_back(std::make_unique<Condition>(std::bind(&NPC::bulletDetected, this)));
		dashSequenceChildren.push_back(std::make_unique<DashNode>(m_dashBehaviour));
		std::unique_ptr<Sequence> dashSequence = std::make_unique<Sequence>(std::move(dashSequenceChildren));

		std::vector<std::unique_ptr<DecisionNode>> attackSequenceChildren;
		// should we attack
		attackSequenceChildren.push_back(std::make_unique<Condition>(std::bind(&NPC::attackPlayer, this)));

		std::vector<std::unique_ptr<DecisionNode>> attackDodgeSequence;
		attackDodgeSequence.push_back(std::move(dashSequence));// check dodge
		attackDodgeSequence.push_back(std::make_unique<AttackingNode>(attack)); // else attack

		std::unique_ptr<Selector> attackDodgeSelector = std::make_unique<Selector>(std::move(attackDodgeSequence));

		attackSequenceChildren.push_back(std::move(attackDodgeSelector)); // add to it


		std::unique_ptr<Sequence>  attackSequence = std::make_unique<Sequence>(std::move(attackSequenceChildren));
		selectorChildren.push_back(std::move(deathSequence));
		selectorChildren.push_back(std::move(attackSequence));
	}
	
	

	
	selectorChildren.push_back(std::make_unique<WanderNode>(wander)); // else wander

	m_behaviourTree = std::make_unique<Selector>(std::move(selectorChildren));

	/*m_agent.m_user.push_back(wander);*/
}

bool NPC::bulletDetected()
{
	if (!m_dashed)
	{
		if (!m_startDashing)
		{
			Node* currentNode = m_grid->cellSelection(m_body.getPosition())->getNode();
			std::vector<Node*> neighbours = currentNode->getNeighbours();

			for (int i = 0; i < neighbours.size(); i++)
			{
				std::unordered_set<GameObject*> gameobjects = m_grid->m_cells[neighbours[i]->m_row][neighbours[i]->m_column].getGameObjects();

				for (GameObject* gameobject : gameobjects)
				{
					sf::Vector2f bulletDirection = static_cast<Bullet*>(gameobject)->m_velocity;
					sf::Vector2f dir = VectorMath::unitVector(bulletDirection);
					if (gameobject->m_tag == Bullet_Player)
					{
						m_startDashing = true;
						m_dashed = true;
						if (gameobject->m_body.getPosition().x > m_body.getPosition().x)
						{
							m_body.setScale(-1, 1);
							m_dashBehaviour->m_dashDirection = { dir.y, -dir.x };
						}
						else
						{
							m_body.setScale(1, 1);
							m_dashBehaviour->m_dashDirection = { -dir.y, dir.x };
						}
						return true;
					}
				}
			}
		}
	}
	
	

	return m_startDashing;
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


	if (!m_startedAttacking )
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

bool NPC::dead()
{
	m_active = false; 
	return m_health <= 0;
}

void NPC::collisionWith(Tag t_tag)
{

	if (t_tag == Bullet_Player)
	{
		m_health -= 20;
		m_startedAttacking = true;
	}
}


