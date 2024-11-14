#include "SceneState.h"
SceneState::SceneState(Scene* t_newScene) : currentScene(t_newScene)
{
	currentScene = t_newScene;
}

void SceneState::switchScene(Scene* t_newScene)
{

	delete currentScene;
	currentScene = t_newScene;
}
