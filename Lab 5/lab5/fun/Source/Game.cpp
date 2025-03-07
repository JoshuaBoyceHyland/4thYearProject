/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 32U }, "SFML Game", sf::Style::Fullscreen },
	m_exitGame{ false },
	m_sceneManager(m_window)
{

	WorldItemLibrary* lbrary = WorldItemLibrary::getInstance();
	lbrary->setFunction(std::bind(&SceneManager::switchScene, &m_sceneManager, std::placeholders::_1));
	lbrary->loadTextures();
	m_sceneManager.switchScene(BaseGameplay);

	
	
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
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
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
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


