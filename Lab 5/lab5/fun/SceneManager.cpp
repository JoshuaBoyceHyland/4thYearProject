#include "SceneManager.h"

SceneManager::SceneManager(sf::RenderWindow& t_window) : m_window( t_window)
{
}

void SceneManager::switchScene(SceneType t_newScene)
{

	if (m_currentScene != nullptr)
	{
		delete m_currentScene;
	}

	switch (t_newScene)
	{
	case Menu:
		//m_currentScene = new MenuScene(m_window);
		break;
	case Editor:
		m_currentScene = new EditorScene(m_window);
		break;
	default:
		break;
	}
}

Scene* SceneManager::getCurrentScene()
{
	return m_currentScene;
}
