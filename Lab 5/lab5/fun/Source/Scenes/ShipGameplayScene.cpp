#include "Scenes/ShipGameplayScene.h"

ShipGameplayScene::ShipGameplayScene(sf::RenderWindow& t_window) : 
	Scene(t_window), 
	m_uiBorder( "Gameplay"),
	m_camera( m_window)
{
	m_dungeon = m_dungeonGeneratior.generate();

	m_dungeon->m_tag = Enemy_Base;
	m_dungeon->setForGamePlay();

	
	



	GameData* gameData = GameData::getInstance();

	m_playerShip = (*gameData->m_player);

	
	m_grid = gameData->m_currentMap;

	m_playerShip.setPosition(m_grid->m_cells[0][0].m_body.getPosition());
	sf::Vector2f t_centerPosition = m_grid->m_cells[0][0].m_body.getPosition();
	float radiusFromBase = 10000;
	float randoMAngle = rand() % 360;

	sf::Vector2f startPosition = { radiusFromBase, 0.0f };

	sf::Vector2f rotatedVector = RotationMath::rotatedVector(startPosition, randoMAngle);

	sf::Vector2 randomPointAroundBase = startPosition + rotatedVector;

	m_dungeon->setPosition(randomPointAroundBase);

	m_playerShip.m_grids = { m_grid, m_dungeon };
	m_minimap = new MiniMap(t_window, 1.5f, &m_playerShip, {m_grid, m_dungeon }, { m_grid, m_dungeon });
}

void ShipGameplayScene::update(sf::Time t_deltaTime)
{
	

	m_camera.follow(m_playerShip.getPosition());
	m_camera.update();
	m_playerShip.update(t_deltaTime.asMilliseconds());
	m_minimap->update();
}

void ShipGameplayScene::render()
{
	
	m_window.clear(sf::Color::Black);
	m_window.setView(m_camera.getView());
	m_playerShip.draw(m_window);
	m_grid->draw(m_window);
	m_dungeon->draw(m_window);

	m_minimap->drawBackground();
	m_minimap->drawContents();
	m_minimap->drawBorder();
	//m_uiBorder.draw(m_window);
	
	
	
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
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
}
