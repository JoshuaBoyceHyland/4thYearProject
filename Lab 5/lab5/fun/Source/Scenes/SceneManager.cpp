#include "Scenes/SceneManager.h"

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
	case RoomBuilder:
		m_currentScene = new RoomBuilderScene(m_window, std::bind(&SceneManager::switchScene, this, std::placeholders::_1));
		break;
	case BaseBuilder:
		m_currentScene = new BaseBuilderScene(m_window, std::bind(&SceneManager::switchScene, this, std::placeholders::_1));
		break;
	case BaseGameplay:
		m_currentScene = new BaseGameplayScene(m_window);
		break;
	case ShipEditor:
		m_currentScene = new ShipEditorScene(m_window);
		break;
	case ShipGameplay:
		m_currentScene = new ShipGameplayScene(m_window, std::bind(&SceneManager::switchScene, this, std::placeholders::_1));
		break;
	case DungeonGenerationTest:
		m_currentScene = new DungeonGenerationTestScene(m_window);
		break;
	case GeneratedDungionNPCTest:
		m_currentScene =  new GeneratedDungionNPCTestScene(m_window);
		break;
	case EnemyBase:
		m_currentScene = new EnemyBaseScene(m_window, std::bind(&SceneManager::switchScene, this, std::placeholders::_1));
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
