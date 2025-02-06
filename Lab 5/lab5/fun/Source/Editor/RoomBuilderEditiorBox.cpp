#include "Editor/RoomEditiorBox.h"

RoomBuilderEditorBox::RoomBuilderEditorBox()
{
	m_title.setString(resourceString[m_currentPart]);
	sf::FloatRect textSize = m_title.getLocalBounds();
	m_title.setOrigin(textSize.width / 2, textSize.height / 2);
	setUpUiSprites();
}

void RoomBuilderEditorBox::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_uiBox);
	t_window.draw(m_title);
	t_window.draw(m_button);
	t_window.draw(m_button2);
	
	for (int i = 0; i < m_uiRooms[m_currentPart].size(); i++)
	{
		m_uiRooms[m_currentPart][i].draw(t_window);
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
}

void RoomBuilderEditorBox::updateScale(float t_scale)
{
	m_uiBox.scale(t_scale, t_scale);
	m_title.scale(t_scale, t_scale);
	m_button.scale(t_scale, t_scale);
	m_button2.scale(t_scale, t_scale);
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

void RoomBuilderEditorBox::scaleGridForUI(Grid& t_grid)
{

	float scale = 0.1f;
	float XIncrement = t_grid.m_cells[0][0].m_body.getSize().x * scale;
	float YIncrement = t_grid.m_cells[0][0].m_body.getSize().y * scale;

	sf::Vector2f currentPosition = t_grid.m_cells[0][0].m_body.getPosition();
	float startX = currentPosition.x;
	float startY = currentPosition.y;
	

	for (int row = 0; row < t_grid.m_cells.size(); row++)
	{
		

		for (int column = 0; column < t_grid.m_cells[row].size(); column++)
		{
			startX = t_grid.m_cells[row][0].m_body.getPosition().x;

			t_grid.m_cells[row][column].m_body.scale({ scale, scale });
			t_grid.m_cells[row][column].setPosition({ currentPosition });

			currentPosition.x += XIncrement;
		}
		currentPosition.x = startX;
		currentPosition.y += YIncrement;
	}
	
}

Room* RoomBuilderEditorBox::roomSelectionCheck(sf::Vector2f t_mousePosition)
{
	return nullptr;
}

bool RoomBuilderEditorBox::contains(sf::Vector2f t_mousePosition)
{
	return m_uiBox.getGlobalBounds().contains(t_mousePosition);
}

void RoomBuilderEditorBox::updatePosition(sf::Vector2f t_position)
{
	float outlineThickness = (Globals::SCREEN_WIDTH / 100) * m_uiBox.getScale().x;

	m_uiBox.setPosition(t_position.x + outlineThickness, t_position.y + outlineThickness);

	m_title.setPosition({
						(m_uiBox.getPosition().x + ((m_uiBox.getSize().x / 2) * m_uiBox.getScale().x))  /*- m_title.getCharacterSize() - Globals::SCREEN_WIDTH / SCALING*/,
						m_uiBox.getPosition().y + ((Globals::SCREEN_WIDTH / 100) * m_uiBox.getScale().y)
		});

	m_button.setPosition({ m_uiBox.getPosition().x + (m_uiBox.getSize().x * m_uiBox.getScale().x) - ((Globals::SCREEN_WIDTH / 200) * m_uiBox.getScale().x) , m_title.getPosition().y });
	m_button2.setPosition({ m_uiBox.getPosition().x + ((Globals::SCREEN_WIDTH / 200) * m_uiBox.getScale().x)  , m_title.getPosition().y + (20 * m_uiBox.getScale().y) });


	for (int i = 0; i < m_uiRooms.size(); i++)
	{
		sf::Vector2f pos = { m_uiBox.getPosition().x + ((m_uiBox.getSize().x / 2) * m_uiBox.getScale().x) - 50,  m_uiBox.getPosition().y + 200 * m_uiBox.getScale().y };

		for (int k = 0; k < m_uiRooms[ResourceType(i)].size(); k++)
		{

			m_uiRooms[ResourceType(i)][k].setPosition(pos);
			pos.y += 100 * m_uiBox.getScale().y;
		}
	}
}
