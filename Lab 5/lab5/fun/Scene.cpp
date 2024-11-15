#include "Scene.h"

Scene::Scene()
{
}

Scene* Scene::getCurrentScene()
{
	return m_currentScene;
}

void Scene::switchScene(Scene* t_newScene)
{
	delete m_currentScene;
	m_currentScene = t_newScene;
}

void Scene::update(sf::Time t_deltaTime)
{
	
}

void Scene::render()
{
}

void Scene::processKeys(sf::Event t_event)
{
}

void Scene::processMousePress(sf::Event t_event)
{
}

void Scene::processMouseRelease(sf::Event t_event)
{
}

void Scene::processMouseMove(sf::Event t_event)
{
}
