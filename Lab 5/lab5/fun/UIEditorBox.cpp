#include "UIEditorBox.h"

UIEditorBox::UIEditorBox()
{
	setUpRect();
	SetUpText();
	setUpButton();
	setUpUiSprites();
}

void UIEditorBox::draw(sf::RenderWindow& t_window)
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

void UIEditorBox::checkForInteraction(sf::Vector2f t_mousePosition)
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

ShipPart* UIEditorBox::partSelectionCheck(sf::Vector2f t_mousePosition)
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

void UIEditorBox::SetUpText()
{
	Loader* loader = Loader::getInstance();

	m_font = loader->loadFont("ASSETS/FONTS/nulshock.otf");


	m_title.setString("Hulls");
	m_title.setFont((*m_font));
	m_title.setFillColor(sf::Color::Black);
	m_title.setCharacterSize(Globals::SCREEN_WIDTH / SCALING);
	sf::FloatRect textSize = m_title.getLocalBounds();
	m_title.setOrigin(textSize.width / 2, textSize.height / 2);

	m_title.setPosition({
							(m_uiBox.getPosition().x + (m_uiBox.getSize().x / 2))  /*- m_title.getCharacterSize() - Globals::SCREEN_WIDTH / SCALING*/,
							m_uiBox.getPosition().y + (Globals::SCREEN_WIDTH / 100)
		});
}

void UIEditorBox::setUpRect()
{
	float outlineThickness = Globals::SCREEN_WIDTH / 100;
	m_uiBox.setFillColor(m_lightBlue);
	m_uiBox.setOutlineColor(m_darkBlue);
	m_uiBox.setSize({ Globals::SCREEN_WIDTH / 5, Globals::SCREEN_HEIGHT - (outlineThickness * 2) });
	m_uiBox.setOutlineThickness(outlineThickness);
	m_uiBox.setPosition({ outlineThickness, outlineThickness });
}

void UIEditorBox::setUpButton()
{
	m_button.setPointCount(3);
	m_button.setFillColor(m_darkBlue);
	m_button.setPosition({ m_uiBox.getPosition().x + m_uiBox.getSize().x - (Globals::SCREEN_WIDTH / 200), m_title.getPosition().y });
	m_button.setRadius(10);
	m_button.setRotation(90.0f);

	m_button2.setPointCount(3);
	m_button2.setFillColor(m_darkBlue);
	m_button2.setPosition({ m_uiBox.getPosition().x + (Globals::SCREEN_WIDTH / 200)  , m_title.getPosition().y + 20 });
	m_button2.setRadius(10);
	m_button2.setRotation(270.0f);
}

void UIEditorBox::setUpUiSprites()
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
