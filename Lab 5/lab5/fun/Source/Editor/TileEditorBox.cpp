#include "Editor/TileEditorBox.h"

TileEditorBox::TileEditorBox()
{
	m_title.setString(propertyString[m_currentPart]);
	sf::FloatRect textSize = m_title.getLocalBounds();
	m_title.setOrigin(textSize.width / 2, textSize.height / 2);
	setUpUiSprites();
}

void TileEditorBox::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_uiBox);
	t_window.draw(m_title);
	t_window.draw(m_button);
	t_window.draw(m_button2);

	for (int i = 0; i < m_uiSprites[int(m_currentPart)].size(); i++)
	{
		t_window.draw(m_uiSprites[int(m_currentPart)][i]);
	}

}

void TileEditorBox::checkForInteraction(sf::Vector2f t_mousePosition)
{
	if (m_button.getGlobalBounds().contains(t_mousePosition))
	{
		int part = static_cast<int>(m_currentPart);

		part++;
		if (part > NUM_OF_SECTIONS - 1)
		{
			part = 0;
		}

		m_currentPart = TraversalProperty(part);
	}

	if (m_button2.getGlobalBounds().contains(t_mousePosition))
	{
		int part = static_cast<int>(m_currentPart);

		part--;
		if (part < 0)
		{
			part = NUM_OF_SECTIONS - 1;
		}

		m_currentPart = TraversalProperty(part);
	}


	m_title.setString(propertyString[m_currentPart]);
	sf::FloatRect textSize = m_title.getLocalBounds();
	m_title.setOrigin(textSize.width / 2, textSize.height / 2);
}

Tile* TileEditorBox::partSelectionCheck(sf::Vector2f t_mousePosition)
{

	Tile* tile = nullptr;

	for (int i = 0; i < m_uiSprites[(int)m_currentPart].size(); i++)
	{
		if (m_uiSprites[static_cast<int>(m_currentPart)][i].getGlobalBounds().contains(t_mousePosition))
		{
			std::cout << "Contains" << std::endl;
			TileLibrary* library = TileLibrary::getInstance();
			tile = library->getTile(m_currentPart, i);
			tile->setPosition(m_uiSprites[static_cast<int>(m_currentPart)][i].getPosition());
		}
	}

	return tile;

}

bool TileEditorBox::contains(sf::Vector2f t_mousePosition)
{

	return m_uiBox.getGlobalBounds().contains(t_mousePosition);
}

void TileEditorBox::updatePosition(sf::Vector2f t_position)
{
	float outlineThickness = (Globals::SCREEN_WIDTH / 100) * m_uiBox.getScale().x;

	m_uiBox.setPosition(t_position.x + outlineThickness, t_position.y +outlineThickness);

	m_title.setPosition({
						(m_uiBox.getPosition().x + ( (m_uiBox.getSize().x / 2) * m_uiBox.getScale().x) )  /*- m_title.getCharacterSize() - Globals::SCREEN_WIDTH / SCALING*/,
						m_uiBox.getPosition().y + ( (Globals::SCREEN_WIDTH / 100) * m_uiBox.getScale().y)
		});

	m_button.setPosition({ m_uiBox.getPosition().x + ( m_uiBox.getSize().x * m_uiBox.getScale().x) - ( (Globals::SCREEN_WIDTH / 200) * m_uiBox.getScale().x) , m_title.getPosition().y });
	m_button2.setPosition({ m_uiBox.getPosition().x + ((Globals::SCREEN_WIDTH / 200) * m_uiBox.getScale().x)  , m_title.getPosition().y + (20 * m_uiBox.getScale().y)  });


	for (int i = 0; i < m_uiSprites.size(); i++)
	{
		sf::Vector2f pos = { m_uiBox.getPosition().x + ((m_uiBox.getSize().x / 2) * m_uiBox.getScale().x),  m_uiBox.getPosition().y + 200 * m_uiBox.getScale().y };

		for (int k = 0; k < m_uiSprites[i].size(); k++)
		{

			m_uiSprites[i][k].setPosition(pos);
			pos.y += 100 * m_uiBox.getScale().y;
		}
	}
}

void TileEditorBox::updateScale(float t_scale)
{
	m_uiBox.scale(t_scale, t_scale);
	m_title.scale(t_scale, t_scale);
	m_button.scale(t_scale, t_scale);
	m_button2.scale(t_scale, t_scale);

	for (int i = 0; i < m_uiSprites.size(); i++)
	{
		for (int k = 0; k < m_uiSprites[i].size(); k++)
		{
			m_uiSprites[i][k].scale(t_scale, t_scale);
		}
	}
}

void TileEditorBox::setUpUiSprites()
{
	TileLibrary* library = TileLibrary::getInstance();

	for (int section = 0; section < NUM_OF_SECTIONS; section++)
	{
		sf::Vector2f pos = { m_uiBox.getPosition().x + (m_uiBox.getSize().x / 2), 100 };

		m_uiSprites.push_back(std::vector<sf::Sprite>());

		for (int k = 0; k < library->m_quantity[TraversalProperty(section)]; k++)
		{
			Texture* texture = library->getTile(TraversalProperty(section), k)->m_textures[0];
			
			m_uiSprites[section].push_back( sf::Sprite(texture->texture) );
			m_uiSprites[section][k].setPosition(pos);
			m_uiSprites[section][k].setOrigin({ (float)(*texture).texture.getSize().x / 2,(float)(float)(*texture).texture.getSize().y / 2 });
			pos.y += 100;
		}


	}


}
