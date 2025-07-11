#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.h"

/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
/// <summary>
/// Interface Class that all scenes that will inherit from
/// </summary>
class Scene
{

	public:
		Scene(sf::RenderWindow& t_window );

		virtual ~Scene();

		virtual void update(sf::Time t_deltaTime) = 0;

		virtual void render() = 0;

		virtual void processKeys(sf::Event t_event) = 0;

		virtual void processMousePress(sf::Event t_event) = 0;

		virtual void processMouseRelease(sf::Event t_event) = 0;

		virtual void processMouseMove(sf::Event t_event) = 0;

		virtual void processMouseWheel(sf::Event t_event) = 0;
	
	protected:

		sf::RenderWindow& m_window;
};