#pragma once

#include "EditorScene.h"
#include "ShipPart.h"
#include "GameplayScene.h"

enum SceneType{ Menu, Editor, Gameplay };

class SceneManager
{
	public:
		SceneManager(sf::RenderWindow& t_window);

		void switchScene(SceneType t_newScene);
		Scene* getCurrentScene();

	private:

		SceneType m_currentSceneType;
		Scene* m_currentScene = nullptr;
		sf::RenderWindow& m_window;
};

