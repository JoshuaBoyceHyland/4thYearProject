#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>

#include "Globals.h"
#include <SFML/Graphics.hpp>

#include "EditorScene.h"
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

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game


	Scene* m_scene;
};


#endif // !GAME_HPP

