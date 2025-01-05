#include "ShipPartEditiorBox.h"

ShipPartEditiorBox::ShipPartEditiorBox()
{
	setUpUiSprites();
}


ShipPart* ShipPartEditiorBox::partSelectionCheck(sf::Vector2f t_mousePosition)
{
	ShipPart* part = nullptr;
	
	for (int i = 0; i < PartsLibarary::NUM_OF_EACH_PART; i++)
	{
		if (m_uiSprites[static_cast<int>(current)][i].getGlobalBounds().contains(t_mousePosition))
		{
			PartsLibarary* library = PartsLibarary::getInstance();
			part = library->getPart(current, i);
			//part->setPosition(m_uiSprites[static_cast<int>(current)][i].getPosition());
		}
	}

	return part;
}


void ShipPartEditiorBox::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_uiBox);
	t_window.draw(m_title);
	t_window.draw(m_button);
	t_window.draw(m_button2);

	for (int i = 0; i < PartsLibarary::NUM_OF_EACH_PART; i++)
	{
		t_window.draw(m_uiSprites[static_cast<int>(current)][i]);
	}
}

void ShipPartEditiorBox::checkForInteraction(sf::Vector2f t_mousePosition)
{
	if (m_button.getGlobalBounds().contains(t_mousePosition))
	{
		int part = static_cast<int>(current);

		part++;
		if (part > 4)
		{
			part = 0;
		}

		current = PartType(part);
	}

	if (m_button2.getGlobalBounds().contains(t_mousePosition))
	{
		int part = static_cast<int>(current);

		part--;
		if (part < 0)
		{
			part = 4;
		}

		current = PartType(part);
	}


	m_title.setString(partTypeString[current]);
	sf::FloatRect textSize = m_title.getLocalBounds();
	m_title.setOrigin(textSize.width / 2, textSize.height / 2);
}

void ShipPartEditiorBox::setUpUiSprites()
{
	PartsLibarary* library = PartsLibarary::getInstance();
	
	sf::Vector2f pos = { m_uiBox.getPosition().x + (m_uiBox.getSize().x / 2), 200 };
	
	for (int i = 0; i < library->NUM_OF_EACH_PART; i++)
	{
		m_uiSprites[static_cast<int>(PartType::CockPit)].push_back((*library->getCockpit(i)).m_body);
		m_uiSprites[static_cast<int>(PartType::CockPit)][i].setPosition(pos);

		m_uiSprites[static_cast<int>(PartType::Hull)].push_back((*library->getHullPart(i)).m_body);
		m_uiSprites[static_cast<int>(PartType::Hull)][i].setPosition(pos);

		m_uiSprites[static_cast<int>(PartType::Thruster)].push_back((*library->getGetThruster(i)).m_body);
		m_uiSprites[static_cast<int>(PartType::Thruster)][i].setPosition(pos);

		m_uiSprites[static_cast<int>(PartType::Left_Wing)].push_back((*library->getLeftWing(i)).m_body);
		m_uiSprites[static_cast<int>(PartType::Left_Wing)][i].setPosition(pos);

		m_uiSprites[static_cast<int>(PartType::Right_Wing)].push_back((*library->getRightWing(i)).m_body);
		m_uiSprites[static_cast<int>(PartType::Right_Wing)][i].setPosition(pos);
		pos.y += 200;
	}
}
