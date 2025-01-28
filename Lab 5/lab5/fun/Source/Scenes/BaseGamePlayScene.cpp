#include "Scenes/BaseGameplayScene.h"

BaseGameplayScene::BaseGameplayScene(sf::RenderWindow& t_window) :
	Scene(t_window),
	m_camera(m_window)
{
	GameData* gamedata = GameData::getInstance();
	m_grid = gamedata->m_currentMap;
	m_grid->setForGamePlay();
	m_npc = new NPC(m_grid, { 2500, 900 });
}



void BaseGameplayScene::update(sf::Time t_deltaTime)
{
	m_npc->update(t_deltaTime.asMilliseconds());
	m_camera.update();
}

void BaseGameplayScene::render()
{
	m_window.clear();
	m_grid->draw(m_window);
	m_npc->draw(m_window);

	m_window.display();
}


void BaseGameplayScene::processKeys(sf::Event t_event)
{
}

void BaseGameplayScene::processMousePress(sf::Event t_event)
{

	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.startMove();
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
		m_camera.endMove();
	}
}

void BaseGameplayScene::processMouseMove(sf::Event t_event)
{
	m_camera.move();
}

void BaseGameplayScene::processMouseWheel(sf::Event t_event)
{
	std::cout << m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)).x << " " << m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)).y << std::endl;
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
}
