#include "Scenes/DungeonGenerationTest.h"

DungeonGenerationTestScene::DungeonGenerationTestScene(sf::RenderWindow& t_window) :
	Scene( t_window), 
	m_camera(m_window)
{
}

void DungeonGenerationTestScene::update(sf::Time t_deltaTime)
{
	m_camera.update();
}

void DungeonGenerationTestScene::render()
{
	m_window.clear();
	sf::CircleShape t;
	t.setFillColor(sf::Color::Yellow);
	t.setPosition(Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2);
	t.setRadius(100);
	t.setOrigin(50, 50);
	m_window.draw(t);
	m_window.display();
}

void DungeonGenerationTestScene::processKeys(sf::Event t_event)
{

}

void DungeonGenerationTestScene::processMousePress(sf::Event t_event)
{
	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.startMove();
	}
}

void DungeonGenerationTestScene::processMouseRelease(sf::Event t_event)
{

	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.endMove();
	}
}

void DungeonGenerationTestScene::processMouseMove(sf::Event t_event)
{



	m_camera.move();
}

void DungeonGenerationTestScene::processMouseWheel(sf::Event t_event)
{
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
}
