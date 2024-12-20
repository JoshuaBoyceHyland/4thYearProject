#include "EditorScene.h"

EditorScene::EditorScene(sf::RenderWindow& t_window) : Scene(t_window), m_uiBorder( "Editor")
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
	m_window.clear(sf::Color::Black);
	m_uiBorder.draw(m_window);
	m_ui.draw(m_window);

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
}

void EditorScene::processMousePress(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.key.code)
	{

		m_mouse.checkForPartSelection();


		m_ui.checkForInteraction(m_mouse.m_position);

		ShipPart* possiblePart = m_ui.partSelectionCheck(m_mouse.m_position);

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

Ship EditorScene::getCreatedShip()
{
	Ship createdShip;
	
	for (ShipPart* part : m_parts)
	{
		createdShip.setPart((*part));
	}
	
	return createdShip;
}
