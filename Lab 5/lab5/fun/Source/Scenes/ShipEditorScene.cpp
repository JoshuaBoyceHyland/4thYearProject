#include "Scenes/ShipEditorScene.h"

ShipEditorScene::ShipEditorScene(sf::RenderWindow& t_window) : Scene(t_window), m_uiBorder( "Editor")
{
	m_mouse.m_partsInScene = m_parts; 
	m_window.setView(m_window.getDefaultView());
}

ShipEditorScene::~ShipEditorScene()
{
	
	saveCreatedShip();
}

void ShipEditorScene::update(sf::Time t_deltaTime)
{
	m_mouse.update();

	for (int i = 0; i < m_parts.size(); i++)
	{
		m_parts[i]->update();
	}
	if (m_mouse.test != nullptr)
	{
		m_mouse.test->update();
	}
}

void ShipEditorScene::render()
{
	m_window.clear(sf::Color::Black);

	m_uiBorder.draw(m_window);
	m_ui.draw(m_window);

	for (int i = 0; i < m_parts.size(); i++)
	{
		m_parts[i]->draw(m_window);
	}

	if (m_mouse.test != nullptr)
	{
		m_mouse.test->draw(m_window);
	}
	
	m_window.display();
}

void ShipEditorScene::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_window.close();
	}
}

void ShipEditorScene::processMousePress(sf::Event t_event)
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

void ShipEditorScene::processMouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.key.code)
	{
		m_mouse.releaseSelectedPart();
		
	}

	if (sf::Mouse::Right == t_event.key.code)
	{
		m_mouse.checkForOriginSelection();
	}
}

void ShipEditorScene::processMouseMove(sf::Event t_event)
{
	m_mouse.m_position = { static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y) };
}

Ship ShipEditorScene::getCreatedShip()
{
	Ship createdShip;
	
	for (ShipPart* part : m_parts)
	{
		for (int i = 0; i < part->getConnectors()->connectionPoints.size(); i++)
		{
			if (part->getConnectors()->connectionPoints[i].connectedTo != nullptr)
			{
				createdShip.setPart((*part));
				break;
			}
		}
		
	}
	
	return createdShip;
}

void ShipEditorScene::saveCreatedShip()
{
	GameData* gameData = GameData::getInstance();

	gameData->getPlayerShip();


	Ship createdShip;


	createdShip.setOrigin((*m_mouse.m_shipOrigin).m_body.getPosition());

	for (ShipPart* part : m_parts)
	{
		for (int i = 0; i < part->getConnectors()->connectionPoints.size(); i++)
		{
			if (part->getConnectors()->connectionPoints[i].connectedTo != nullptr)
			{
				createdShip.setPart((*part));
				break;
			}
		}

	}

	saver.saveShip(&createdShip);
	gameData->m_playerShip = new Ship(createdShip);
}

void ShipEditorScene::processMouseWheel(sf::Event t_event)
{
}
