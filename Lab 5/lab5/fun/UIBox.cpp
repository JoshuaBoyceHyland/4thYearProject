#include "UIBox.h"

UIBox::UIBox()
{
	setUpRect();
	SetUpText();
	setUpButton();
}

void UIBox::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_uiBox);
	t_window.draw(m_title);
	t_window.draw(m_button);
	t_window.draw(m_button2);
}

void UIBox::checkForButtonInteraction(sf::Vector2f t_mousePosition)
{
	if (m_button.getGlobalBounds().contains(t_mousePosition))
	{
		int part = static_cast<int>( current);
		
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
}

void UIBox::SetUpText()
{
	Loader* loader = Loader::getInstance();

	m_font = loader->loadFont("ASSETS/FONTS/nulshock.otf");

	m_title.setString("Hulls");
	m_title.setFont((*m_font));
	m_title.setFillColor(sf::Color::Black);
	
	m_title.setCharacterSize(Globals::SCREEN_WIDTH / 100);
	m_title.setPosition({ m_uiBox.getPosition().x + (m_uiBox.getSize().x / 2) - m_title.getCharacterSize() - Globals::SCREEN_WIDTH / 100, Globals::SCREEN_WIDTH / 100});

}

void UIBox::setUpRect()
{
	float outlineThickness = Globals::SCREEN_WIDTH / 100;
	m_uiBox.setFillColor(m_lightBlue);
	m_uiBox.setOutlineColor(m_darkBlue);
	m_uiBox.setSize({ Globals::SCREEN_WIDTH / 5, Globals::SCREEN_HEIGHT - (outlineThickness * 2) });
	m_uiBox.setOutlineThickness(outlineThickness);
	m_uiBox.setPosition({ outlineThickness, outlineThickness });
}

void UIBox::setUpButton()
{
	m_button.setPointCount(3);
	m_button.setFillColor(m_darkBlue);
	m_button.setPosition({ m_title.getPosition().x + 220, m_title.getPosition().y });
	m_button.setRadius(10);
	m_button.setRotation(90.0f);

	m_button2.setPointCount(3);
	m_button2.setFillColor(m_darkBlue);
	m_button2.setPosition({ m_title.getPosition().x - 150 , m_title.getPosition().y + 20 });
	m_button2.setRadius(10);
	m_button2.setRotation(270.0f);
}