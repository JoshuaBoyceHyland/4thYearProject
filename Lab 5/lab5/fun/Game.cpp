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
	m_window{ sf::VideoMode{ Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 32U }, "SFML Game" },
	m_exitGame{ false }/*,
	m_player({ 100,100 })*/
{
	m_mouse.m_position= { static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y) };
	Loader* loader = Loader::getInstance();

	m_hullTexture = loader->loadTexture("ASSETS/IMAGES/hull/hull_1.png");
	m_thrusterTexture = loader->loadTexture("ASSETS/IMAGES/thruster/thruster_1.png");
	m_pitTexture = loader->loadTexture("ASSETS/IMAGES/cockpits/cockpit_1.png");

	sf::Vector2f pos = { 100, 100 };
	for (int i = 0; i < NUM_OF_PARTS; i++)
	{

		m_parts.push_back(new ShipPart(m_hullTexture, pos));
		pos.x += 300;
	}
	m_mouse.m_partsInScene = m_parts;
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
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
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
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if ( sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMousePress(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseRelease(newEvent);
		}
		if (sf::Event::MouseMoved == newEvent.type)
		{
			processMouseMove(newEvent);
		}
	}
}

//
///// <summary>
///// deal with key presses from the user
///// </summary>
///// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	if (sf::Keyboard::E == t_event.key.code)
	{
		m_parts.push_back(new ShipPart(m_hullTexture, { 100, 100 }));
		NUM_OF_PARTS++;
		m_mouse.m_partsInScene = m_parts;
	}

	if (sf::Keyboard::Q == t_event.key.code)
	{
		m_parts.push_back(new ShipPart(m_thrusterTexture, { 100, 100 }));
		NUM_OF_PARTS++;
		m_mouse.m_partsInScene = m_parts;
	}

	if (sf::Keyboard::W == t_event.key.code)
	{
		m_parts.push_back(new ShipPart(m_pitTexture, { 100, 100 }));
		NUM_OF_PARTS++;
		m_mouse.m_partsInScene = m_parts;
	}
	
}

void Game::processMousePress(sf::Event t_event)
{

	if (sf::Mouse::Left == t_event.key.code)
	{
		m_mouse.checkForPartSelection();
		
	}
}

void Game::processMouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.key.code)
	{
		m_mouse.releaseSelectedPart();

	}
	
}

void Game::processMouseMove(sf::Event t_event)
{
	//std::cout << "Mouse move" << std::endl;
	m_mouse.m_position = { static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y) };
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	
	if (m_exitGame)
	{
		m_window.close();
	}

	m_mouse.update();

	for (int i = 0; i < NUM_OF_PARTS; i++)
	{
		m_parts[i]->update();
	}

	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	for (int i = 0; i < NUM_OF_PARTS; i++)
	{
		m_parts[i]->draw(m_window);
	}
	m_window.display();
}

