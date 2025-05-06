#pragma once

#include "SceneTypes.h"
#include "Scenes/ShipEditorScene.h"
#include "Ship/ShipPart.h"
#include "Scenes/ShipGameplayScene.h"
#include "Scenes/RoomBuilderScene.h"
#include "Scenes/BaseBuilderScene.h"
#include "Scenes/BaseGameplayScene.h"
#include "Scenes/DungeonGenerationTest.h"
#include "Scenes/GeneratedDungionNPCTest.h"
#include "Scenes/EnemyBaseScene.h"

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

