#include "Scenes/DungeonGenerationTest.h"

DungeonGenerationTestScene::DungeonGenerationTestScene(sf::RenderWindow& t_window) :
	Scene( t_window), 
	m_camera(m_window)
{
	dungeon = m_dg.generate(); // comment this if you want to step through the generation
	//m_dg.generateInitialGrids(); // uncomment to generate the grids
}

void DungeonGenerationTestScene::update(sf::Time t_deltaTime)
{
	m_camera.update();
	//m_dg.generationLoopStepThrough(); //uncomment to step through the generation

}

void DungeonGenerationTestScene::render()
{


	
	m_window.clear();
	//m_dg.draw(m_window);
	dungeon->m_grid->draw(m_window);
	
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
