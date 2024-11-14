#pragma once
#include "Scene.h"
#include "Ship.h"

class SceneState
{
	public:
		SceneState(Scene* t_newScene);
		void switchScene(Scene* t_newScene);

	private:
		Scene* currentScene;
		Ship* m_player;
};

