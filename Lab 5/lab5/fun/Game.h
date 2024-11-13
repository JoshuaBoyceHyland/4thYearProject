/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>

#include "Globals.h"
#include <SFML/Graphics.hpp>
#include "EditorMouse.h"
#include "ShipPart.h"
#include "Loader.h"
#include "PartsLibarary.h"
#include "UIBox.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMousePress(sf::Event t_event);
	void processMouseRelease(sf::Event t_event);
	void processMouseMove(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();


	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game



	std::vector<ShipPart*> m_parts;

	EditorMouse m_mouse;
	UIBox ui;
};


#endif // !GAME_HPP

