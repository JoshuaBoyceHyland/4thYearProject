#include "UI/UIEditorBox.h"

UIEditorBox::UIEditorBox()
{
	setUpRect();
	SetUpText();
	setUpButton();
}

void UIEditorBox::setButtonFunction(std::function<void(SceneType)> t_sceneChangeFunction)
{
	button->setFunction(t_sceneChangeFunction);
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

	button = new Button();
	button->setShapeType(new sf::RectangleShape({ Globals::SCREEN_WIDTH / 15, Globals::SCREEN_HEIGHT / 35  }));
	button->getShape()->setFillColor(m_lightBlue);
	button->getShape()->setOutlineColor(m_darkBlue);
	button->getShape()->setOutlineThickness(Globals::SCREEN_WIDTH / 200);
	button->getShape()->setPosition({ -200 , -400 });
	
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

