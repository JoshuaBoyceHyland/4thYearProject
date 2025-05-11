#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 32U }, "SFML Game"/*, sf::Style::Fullscreen*/ },
	m_exitGame{ false },
	m_sceneManager(m_window)
{

	WorldItemLibrary* lbrary = WorldItemLibrary::getInstance();
	lbrary->setFunction(std::bind(&SceneManager::switchScene, &m_sceneManager, std::placeholders::_1));
	lbrary->loadTextures();
	//m_sceneManager.switchScene(DungeonGenerationTest);
	m_sceneManager.switchScene(BaseGameplay);
	
	
}

Game::~Game()
{
}

void Game::run()
{	

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			m_sceneManager.getCurrentScene()->update(timePerFrame); //60 fps
		}
		m_sceneManager.getCurrentScene()->render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_exitGame = true;
		}

		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			m_sceneManager.getCurrentScene()->processKeys(newEvent);

			if (sf::Keyboard::G == newEvent.key.code)
			{
				m_sceneManager.switchScene(ShipGameplay);
			}


			if (sf::Keyboard::L == newEvent.key.code)
			{
				m_sceneManager.switchScene(BaseGameplay);
			}
		}
		if ( sf::Event::MouseButtonPressed == newEvent.type)
		{
			m_sceneManager.getCurrentScene()->processMousePress(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			m_sceneManager.getCurrentScene()->processMouseRelease(newEvent);
		}
		if (sf::Event::MouseMoved == newEvent.type)
		{
			m_sceneManager.getCurrentScene()->processMouseMove(newEvent);
		}

		if( sf::Event::MouseWheelMoved == newEvent.type)
		{
			m_sceneManager.getCurrentScene()->processMouseWheel(newEvent);
		}
	}
}


