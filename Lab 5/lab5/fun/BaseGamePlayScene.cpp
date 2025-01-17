#include "BaseGameplayScene.h"

BaseGameplayScene::BaseGameplayScene(sf::RenderWindow& t_window) :
	Scene(t_window),
	m_camera(m_window)
{
	GameData* gamedata = GameData::getInstance();
	m_grid = gamedata->m_currentMap;
	m_grid->setForGamePlay();
}



void BaseGameplayScene::update(sf::Time t_deltaTime)
{
	m_camera.update();
}

void BaseGameplayScene::render()
{
	m_window.clear();
	m_grid->draw(m_window);


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
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
}
