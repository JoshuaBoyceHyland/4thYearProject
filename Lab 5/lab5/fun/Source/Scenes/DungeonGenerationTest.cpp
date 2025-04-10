#include "Scenes/DungeonGenerationTest.h"

DungeonGenerationTestScene::DungeonGenerationTestScene(sf::RenderWindow& t_window) :
	Scene( t_window), 
	m_camera(m_window), 
	m_dg( new DungeonGeneration)
{
	m_dg->generateRooms();
	m_camera.zoom(-200);
	uiView.setSize(m_window.getSize().x, m_window.getSize().y);
	uiView.setCenter(m_window.getSize().x / 2, m_window.getSize().y / 2);
}

void DungeonGenerationTestScene::update(sf::Time t_deltaTime)
{
	uiView.setCenter(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
	m_camera.update();
	m_dg->update();

}

void DungeonGenerationTestScene::render()
{


	
	m_window.clear();
	m_window.setView(m_camera.m_camera);
	m_dg->draw(m_window);

	m_window.setView(uiView);
	m_window.draw(m_dg->m_stateText);

	if (m_dg->waitingForNextState && m_dg->state != GenerationState::Done)
	{
		m_window.draw(m_dg->m_continueText);
	}

	m_window.draw(m_dg->m_restartText);

	m_window.display();
}

void DungeonGenerationTestScene::processKeys(sf::Event t_event)
{
	
	if (sf::Keyboard::Space == t_event.key.code)
	{
		m_dg->waitingForNextState = false;
	}

	if (sf::Keyboard::R== t_event.key.code) 
	{
		delete m_dg;
		m_dg = nullptr;
		m_dg = new DungeonGeneration();
		m_dg->generateRooms();
	}
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
