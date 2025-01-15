#include "BaseGamePlayScene.h"

BaseGamePlayScene::BaseGamePlayScene(sf::RenderWindow& t_window) :
	Scene(m_window)
{
	GameData* gameData = GameData::getInstance();
	m_map = new Grid(50, 50, 100, 100, { 0,0 });
	saver.loadMap(m_map);
	
}

void BaseGamePlayScene::update(sf::Time t_deltaTime)
{
}

void BaseGamePlayScene::render()
{
	m_map->draw(m_window);
}

void BaseGamePlayScene::processKeys(sf::Event t_event)
{
}

void BaseGamePlayScene::processMousePress(sf::Event t_event)
{
}

void BaseGamePlayScene::processMouseRelease(sf::Event t_event)
{
}

void BaseGamePlayScene::processMouseMove(sf::Event t_event)
{
}

void BaseGamePlayScene::processMouseWheel(sf::Event t_event)
{
}
