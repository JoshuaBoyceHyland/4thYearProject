#pragma once
//#include "MenuScene.h"
#include "EditorScene.h"

enum SceneType{ Menu, Editor };

class SceneManager
{
	public:
		SceneManager(sf::RenderWindow& t_window);

		void switchScene(SceneType t_newScene);
		Scene* getCurrentScene();

	private:

		Scene* m_currentScene = nullptr;
		sf::RenderWindow& m_window;
};

