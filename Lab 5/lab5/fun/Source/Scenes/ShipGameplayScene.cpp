#include "Scenes/ShipGameplayScene.h"

ShipGameplayScene::ShipGameplayScene(sf::RenderWindow& t_window) : 
	Scene(t_window), 
	m_uiBorder( "Gameplay"),
	m_camera( m_window)
{
	GameData* gameData = GameData::getInstance();

	m_player = (*gameData->m_player);
	
	m_grid = gameData->m_currentMap;

	m_dungeon = m_generator.generate();


	float angle = static_cast<float>(rand()) / RAND_MAX * 2 * RotationMath::PI;
	float radius = sqrt(static_cast<float>(rand()) / RAND_MAX) * 10000;

	float dx = cos(angle) * radius;
	float dy = sin(angle) * radius;

	float randomX = m_grid->m_cells[0][0].m_body.getPosition().x + dx;
	float randomY = m_grid->m_cells[0][0].m_body.getPosition().y + dy;
	singal = new SignalIndicaor(&m_player);
	m_dungeon->setPosition({ randomX, randomY });
}

void ShipGameplayScene::update(sf::Time t_deltaTime)
{
	
	
	m_camera.follow(m_player.getPosition());
	m_camera.update();
	m_player.update(t_deltaTime.asMilliseconds());
	singal->update(m_dungeon->m_cells[0][0].m_body.getPosition());
}

void ShipGameplayScene::render()
{

	sf::Vector2f distanceFromDungeon = -  m_player.getPosition(); 
	std::cout << "Distance X: " << distanceFromDungeon.x << " Y: " << distanceFromDungeon.y << std::endl;
	m_window.clear(sf::Color::Black);
	m_player.draw(m_window);
	singal->draw(m_window);
	m_grid->draw(m_window);
	m_dungeon->draw(m_window);

	
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
