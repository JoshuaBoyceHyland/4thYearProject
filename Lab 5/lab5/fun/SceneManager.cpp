#include "SceneManager.h"

SceneManager::SceneManager(sf::RenderWindow& t_window) : m_window( t_window)
{
}

void SceneManager::switchScene(SceneType t_newScene)
{

	switch (t_newScene)
	{
	case Menu:
		//m_currentScene = new MenuScene(m_window);
		break;
	case Editor:
		m_currentScene = new EditorScene(m_window);

		break;
	case Gameplay:
		m_currentScene = new GameplayScene(m_window, dynamic_cast<EditorScene*>(m_currentScene)->getCreatedShip());
		break;
	default:
		break;
	}
	m_currentSceneType = t_newScene;
}

Scene* SceneManager::getCurrentScene()
{
	return m_currentScene;
}
