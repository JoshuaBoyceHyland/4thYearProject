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
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	sf::VertexArray m_points;// vertext arry for ourt drawings
	sf::Color m_colour; // colour ofr next vertex

	//Player m_player;
	sf::Texture m_pitTexture;
	sf::Texture m_hullTexture;
	sf::Texture m_thrusterTexture;
	sf::Texture m_leftWingTexture;
	sf::Texture m_rightWingTexture;

	float m_rotation = 0;
	sf::Vector2f m_position = { 100, 100 };

	int NUM_OF_PARTS = 2;
	std::vector<ShipPart*> m_parts;

	EditorMouse m_mouse;
};


#endif // !GAME_HPP

