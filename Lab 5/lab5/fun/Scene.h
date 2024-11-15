#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"


/// <summary>
/// Interface Class that all scenes that will inherit from
/// </summary>
class Scene
{

	public:

		Scene();

		Scene* getCurrentScene();

		void switchScene(Scene* t_newScene);

		virtual void update(sf::Time t_deltaTime);

		virtual void render();

		virtual void processKeys(sf::Event t_event);

		virtual void processMousePress(sf::Event t_event);

		virtual void processMouseRelease(sf::Event t_event);

		virtual void processMouseMove(sf::Event t_event);

	private:
		Scene* m_currentScene = nullptr;
};