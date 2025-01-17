#include "SceneManager.h"

SceneManager::SceneManager(sf::RenderWindow& t_window) : m_window( t_window)
{
}

void SceneManager::switchScene(SceneType t_newScene)
{


	delete m_currentScene;

	switch (t_newScene)
	{
	case Menu:
		//m_currentScene = new MenuScene(m_window);
		break;

	case BaseBuilder:
		m_currentScene = new BaseBuilderScene(m_window);
		break;
	case BaseGameplay:
		m_currentScene = new BaseGameplayScene(m_window);
		break;
	case Editor:
		m_currentScene = new ShipEditorScene(m_window);

		break;
	case ShipGameplay:
		m_currentScene = new ShipGameplayScene(m_window);
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
