#pragma once

#include "Scenes/EditorScene.h"
#include "Ship/ShipPart.h"
#include "Scenes/GameplayScene.h"
#include "Scenes/RoomBuilderScene.h"
#include "Scenes/BaseBuilderScene.h"
#include "Scenes/BaseGameplayScene.h"

enum SceneType{ Menu, ShipEditor, RoomBuilder,BaseBuilder, BaseGameplay,ShipGameplay };

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

