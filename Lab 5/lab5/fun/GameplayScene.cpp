#include "Include/GameplayScene.h"

ShipGameplayScene::ShipGameplayScene(sf::RenderWindow& t_window) : Scene(t_window), m_uiBorder( "Gameplay")
{
	GameData* gameData = GameData::getInstance();

	m_player = (*gameData->m_player);
}

void ShipGameplayScene::update(sf::Time t_deltaTime)
{
	m_player.update(t_deltaTime.asMilliseconds());
}

void ShipGameplayScene::render()
{
	m_window.clear(sf::Color::Black);
	m_player.draw(m_window);
	m_uiBorder.draw(m_window);
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
