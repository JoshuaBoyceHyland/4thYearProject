#include "Scenes/GeneratedDungionNPCTest.h"

GeneratedDungionNPCTestScene::GeneratedDungionNPCTestScene(sf::RenderWindow& t_window) : 
Scene( t_window), 
m_camera(m_window)
{
	m_dungeon = m_dungeonGenerator.generate();
	m_dungeon->setPosition({ -50, -50 });
	m_dungeon->setForGamePlay();
	
	for (int i = 0; i < 10; i++)
	{

		Cell* randCell = m_dungeon->getRandomTraverableCell();
		m_npc.push_back(new NPC(m_dungeon, randCell->m_body.getPosition()));
	}
}

void GeneratedDungionNPCTestScene::update(sf::Time t_deltaTime)
{
	m_camera.update();

	for (int i = 0; i < m_npc.size(); i++)
	{
		m_npc[i]->update(t_deltaTime.asMilliseconds());
	}
}

void GeneratedDungionNPCTestScene::render()
{
	m_window.clear();
	
	m_dungeon->draw(m_window);
	for (int i = 0; i < m_npc.size(); i++)
	{
		m_npc[i]->draw(m_window);
	}
	m_window.display();
}

void GeneratedDungionNPCTestScene::processKeys(sf::Event t_event)
{
	
}

void GeneratedDungionNPCTestScene::processMousePress(sf::Event t_event)
{

	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.startMove();
	}

}

void GeneratedDungionNPCTestScene::processMouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.endMove();
	}
}

void GeneratedDungionNPCTestScene::processMouseMove(sf::Event t_event)
{
	m_camera.move();
}

void GeneratedDungionNPCTestScene::processMouseWheel(sf::Event t_event)
{
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
}
