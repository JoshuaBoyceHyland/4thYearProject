#include "Editor/RoomEditiorBox.h"

RoomBuilderEditorBox::RoomBuilderEditorBox()
{
	m_title.setString(resourceString[m_currentPart]);
	sf::FloatRect textSize = m_title.getLocalBounds();
	m_title.setOrigin(textSize.width / 2, textSize.height / 2);
	button->setText("Edit Tiles");
	setUpUiSprites();
}

void RoomBuilderEditorBox::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_uiBox);
	t_window.draw(m_title);
	t_window.draw(m_button);
	t_window.draw(m_button2);
	t_window.draw(m_sceneChange);
	button->draw(t_window);
	for (int i = 0; i < m_uiRooms[m_currentPart].size(); i++)
	{
		//m_uiRooms[m_currentPart][i].draw(t_window);
	}
}

void RoomBuilderEditorBox::checkForInteraction(sf::Vector2f t_mousePosition)
{
	if (m_button.getGlobalBounds().contains(t_mousePosition))
	{
		int part = static_cast<int>(m_currentPart);

		part++;
		if (part > NUM_OF_SECTIONS - 1)
		{
			part = 0;
		}

		m_currentPart = ResourceType(part);
	}

	if (m_button2.getGlobalBounds().contains(t_mousePosition))
	{
		int part = static_cast<int>(m_currentPart);

		part--;
		if (part < 0)
		{
			part = NUM_OF_SECTIONS - 1;
		}

		m_currentPart = ResourceType(part);
	}


	m_title.setString(resourceString[m_currentPart]);
	sf::FloatRect textSize = m_title.getLocalBounds();
	m_title.setOrigin(textSize.width / 2, textSize.height / 2);


	button->checkForInteraction(t_mousePosition);
	//if (m_sceneChangeButton.getGlobalBounds().contains(t_mousePosition))
	//{
	//	std::cout << "scene change" << std::endl;
	//}
}

void RoomBuilderEditorBox::updateScale(float t_scale)
{
	m_uiBox.scale(t_scale, t_scale);
	m_title.scale(t_scale, t_scale);
	m_button.scale(t_scale, t_scale);
	m_button2.scale(t_scale, t_scale);
	//m_sceneChange.scale(t_scale, t_scale);
	//m_sceneChangeButton.scale(t_scale, t_scale);
	button->scale(t_scale);
	for (int i = 0; i < m_uiRooms.size(); i++)
	{
		for (int k = 0; k < m_uiRooms[ResourceType(i)].size(); k++)
		{
			m_uiRooms[ResourceType(i)][k].scale(t_scale, t_scale);
		}
	}
}

void RoomBuilderEditorBox::setUpUiSprites()
{

	RoomLibrary* library = RoomLibrary::getInstance();
	
	for (int i = 0; i < library->m_types.size(); i++)
	{
		sf::Vector2f uiPos = { m_uiBox.getPosition().x + (m_uiBox.getSize().x / 2), 100 };

		for (int k = 0; k < library->m_quantity[library->m_types[i]]; k++)
		{
			Room* currentRoom = library->getRoom(library->m_types[i], k);
			Grid roomGrid = currentRoom->getGrid();
			
			roomGrid.setPosition(uiPos);
			roomGrid.scale(0.1f, 0.1f);
			
			m_uiRooms[library->m_types[i]].push_back(roomGrid);
			uiPos.y += 100;
		}
		break;
	}
}

Room* RoomBuilderEditorBox::roomSelectionCheck(sf::Vector2f t_mousePosition)
{
	Room* selectedRoom = nullptr;
	for (int i = 0; i < m_uiRooms[m_currentPart].size(); i++)
	{
		if (m_uiRooms[m_currentPart][i].isInGrid(t_mousePosition))
		{
			RoomLibrary* library = RoomLibrary::getInstance();
			selectedRoom = library->getRoom(m_currentPart, i);
			std::cout << "Was in: "<< i << std::endl;
			break;
		}
	}
	return selectedRoom;
}

bool RoomBuilderEditorBox::contains(sf::Vector2f t_mousePosition)
{
	return m_uiBox.getGlobalBounds().contains(t_mousePosition) || button->getShape()->getGlobalBounds().contains(t_mousePosition);
}

void RoomBuilderEditorBox::updatePosition(sf::Vector2f t_position)
{
	float outlineThickness = (Globals::SCREEN_WIDTH / 100) * m_uiBox.getScale().x;

	m_uiBox.setPosition(t_position.x + outlineThickness, t_position.y + outlineThickness);

	m_title.setPosition({
						(m_uiBox.getPosition().x + ((m_uiBox.getSize().x / 2) * m_uiBox.getScale().x))  /*- m_title.getCharacterSize() - Globals::SCREEN_WIDTH / SCALING*/,
						m_uiBox.getPosition().y + ((Globals::SCREEN_WIDTH / 100) * m_uiBox.getScale().y)
		});

	m_sceneChange.setPosition(
		(m_uiBox.getPosition().x + m_uiBox.getSize().x + (m_uiBox.getOutlineThickness() * 2) + (m_sceneChange.getLocalBounds().width / 2) + Globals::SCREEN_WIDTH / SCALING)  /*- m_title.getCharacterSize() - Globals::SCREEN_WIDTH / SCALING*/,
		m_uiBox.getPosition().y - ((Globals::SCREEN_WIDTH / 100) / 3)
	);
	m_button.setPosition({ m_uiBox.getPosition().x + (m_uiBox.getSize().x * m_uiBox.getScale().x) - ((Globals::SCREEN_WIDTH / 200) * m_uiBox.getScale().x) , m_title.getPosition().y });
	m_button2.setPosition({ m_uiBox.getPosition().x + ((Globals::SCREEN_WIDTH / 200) * m_uiBox.getScale().x)  , m_title.getPosition().y + (20 * m_uiBox.getScale().y) });
	//m_sceneChangeButton.setPosition({ m_sceneChange.getPosition().x , m_sceneChange.getPosition().y + m_sceneChange.getLocalBounds().height * 0.45f });

	for (int i = 0; i < m_uiRooms.size(); i++)
	{
		sf::Vector2f pos = { m_uiBox.getPosition().x + ((m_uiBox.getSize().x / 2) * m_uiBox.getScale().x),  m_uiBox.getPosition().y + 200 * m_uiBox.getScale().y };

		for (int k = 0; k < m_uiRooms[ResourceType(i)].size(); k++)
		{

			m_uiRooms[ResourceType(i)][k].setPosition(pos);
			pos.y += 200 * m_uiBox.getScale().y;
		}
	}
}
