#include "Scenes/ShipGameplayScene.h"

ShipGameplayScene::ShipGameplayScene(sf::RenderWindow& t_window) : 
	Scene(t_window), 
	m_uiBorder( "Gameplay"),
	m_camera( m_window)
{
	GameData* gameData = GameData::getInstance();

	m_player = (*gameData->m_player);
	m_grid = gameData->m_currentMap;
}

void ShipGameplayScene::update(sf::Time t_deltaTime)
{
	

	m_camera.follow(m_player.getPosition());
	m_camera.update();
	m_player.update(t_deltaTime.asMilliseconds());
	m_minimap.update(m_player.getPosition());
}

void ShipGameplayScene::render()
{
	m_window.clear(sf::Color::Black);
	m_window.setView(m_camera.getView());
	m_player.draw(m_window);
	m_grid->draw(m_window);
	
	//m_uiBorder.draw(m_window);
	
	m_window.setView(m_minimap.miniMapView);
	m_player.draw(m_window);
	m_window.display();
}

void ShipGameplayScene::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_window.close();
	}
}

void ShipGameplayScene::processMousePress(sf::Event t_event)
{
}

void ShipGameplayScene::processMouseRelease(sf::Event t_event)
{
}

void ShipGameplayScene::processMouseMove(sf::Event t_event)
{
}

void ShipGameplayScene::processMouseWheel(sf::Event t_event)
{
}
