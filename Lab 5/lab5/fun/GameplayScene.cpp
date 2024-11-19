#include "GameplayScene.h"

GameplayScene::GameplayScene(sf::RenderWindow& t_window, Ship t_player) : Scene(t_window), m_uiBorder( "Gameplay"), m_player( t_player)
{
}

void GameplayScene::update(sf::Time t_deltaTime)
{
	m_player.update(t_deltaTime.asMilliseconds());
}

void GameplayScene::render()
{
	m_window.clear(sf::Color::Black);
	m_uiBorder.draw(m_window);
	m_player.draw(m_window);
	m_window.display();
}

void GameplayScene::processKeys(sf::Event t_event)
{
}

void GameplayScene::processMousePress(sf::Event t_event)
{
}

void GameplayScene::processMouseRelease(sf::Event t_event)
{
}

void GameplayScene::processMouseMove(sf::Event t_event)
{
}
