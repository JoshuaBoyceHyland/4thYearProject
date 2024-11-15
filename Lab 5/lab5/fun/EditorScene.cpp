#include "EditorScene.h"

EditorScene::EditorScene(sf::RenderWindow& t_window, Scene* t_currentScene) : m_window(t_window), m_sceneState( t_currentScene)
{
	m_mouse.m_partsInScene = m_parts; 
}

void EditorScene::update(sf::Time t_deltaTime)
{
	m_mouse.update();

	for (int i = 0; i < m_parts.size(); i++)
	{
		m_parts[i]->update();
	}

}

void EditorScene::render()
{
	m_window.clear(sf::Color::White);
	ui.draw(m_window);

	for (int i = 0; i < m_parts.size(); i++)
	{
		m_parts[i]->draw(m_window);
	}
	m_window.display();
}

void EditorScene::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_window.close();
	}

	if(sf::Keyboard::S== t_event.key.code)
	{
		m_sceneState->switchScene(new EditorScene(m_window, m_sceneState));
	}
}

void EditorScene::processMousePress(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.key.code)
	{

		m_mouse.checkForPartSelection();


		ui.checkForButtonInteraction(m_mouse.m_position);
		ShipPart* possiblePart = ui.partSelectionCheck(m_mouse.m_position);

		if (possiblePart != nullptr)
		{
			m_parts.push_back(new ShipPart(*possiblePart));
			m_mouse.m_partsInScene = m_parts;//update the parts in scene for mouse
			m_mouse.selectPiece(m_parts.size() - 1);
		}

	}
}

void EditorScene::processMouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.key.code)
	{
		m_mouse.releaseSelectedPart();
	}
}

void EditorScene::processMouseMove(sf::Event t_event)
{
	m_mouse.m_position = { static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y) };
}
