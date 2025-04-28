#include "Scenes/BaseGameplayScene.h"

BaseGameplayScene::BaseGameplayScene(sf::RenderWindow& t_window) :
	Scene(t_window),
	m_camera(m_window)
	
{
	GameData* gamedata = GameData::getInstance();
	m_grid = gamedata->m_currentMap;
	saver.loadMapJson(m_grid);
	m_grid->setForGamePlay();
	m_player = new BasePlayer(m_grid);
	for (int i = 0; i < 10; i++)
	{
		m_npc.push_back(new NPC(m_grid, m_player,{ 2500, 900 }));
	}
	
	for (int row = 0; row < m_grid->m_cells.size(); row++)
	{
		for (int column = 0; column < m_grid->m_cells[row].size(); column++)
		{
			if (m_grid->m_cells[row][column].m_cellJob != nullptr)
			{
				jobs.push_back(m_grid->m_cells[row][column].m_cellJob);
			}
		}
	}
}



void BaseGameplayScene::update(sf::Time t_deltaTime)
{
	for (int i = 0; i < m_npc.size(); i++)
	{
		m_npc[i]->update(t_deltaTime.asMilliseconds());
	}

	


	
	m_camera.follow(m_player->getPosition());
	m_camera.update();

	m_player->update(t_deltaTime.asMilliseconds());
}

void BaseGameplayScene::render()
{
	m_window.clear();
	m_grid->draw(m_window);
	for (int i = 0; i < m_npc.size(); i++)
	{
		m_npc[i]->draw(m_window);
	}
	m_player->draw(m_window);
	m_window.display();
}


void BaseGameplayScene::processKeys(sf::Event t_event)
{
}

void BaseGameplayScene::processMousePress(sf::Event t_event)
{

	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		//m_camera.startMove();
	}


	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		//m_grid->pathFind(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
		//m_npc->goTo(m_grid->cellSelection(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)))->getNode());
	}
	if (sf::Mouse::Right == t_event.mouseButton.button)
	{
		m_grid->highlightNeighbours(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
	}

	
}

void BaseGameplayScene::processMouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		//m_camera.endMove();
	}
}

void BaseGameplayScene::processMouseMove(sf::Event t_event)
{
	//m_camera.move();
}

void BaseGameplayScene::processMouseWheel(sf::Event t_event)
{
	std::cout << m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)).x << " " << m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)).y << std::endl;
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
}
