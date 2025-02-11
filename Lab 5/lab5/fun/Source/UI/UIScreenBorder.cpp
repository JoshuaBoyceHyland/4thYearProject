#include "UI/UIScreenBorder.h"

UIScreenBorder::UIScreenBorder(std::string t_title) : m_titleStr( t_title)
{
	setUpBorder();
	setUpTitle();
	setUpTitleBox();
}

void UIScreenBorder::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_border);
	t_window.draw(m_titleBox);
	t_window.draw(m_title);
}

void UIScreenBorder::checkForInteraction(sf::Vector2f t_mousePosition)
{
}

void UIScreenBorder::setUpBorder()
{
	float outLineTHickness = Globals::SCREEN_WIDTH / 100;

	m_border.setSize({ Globals::SCREEN_WIDTH - (outLineTHickness * 2) , Globals::SCREEN_HEIGHT - (outLineTHickness * 2) });
	m_border.setPosition({ outLineTHickness,outLineTHickness });
	m_border.setOutlineThickness(outLineTHickness);
	m_border.setFillColor(sf::Color::Transparent);
	m_border.setOutlineColor(m_darkBlue);
}

void UIScreenBorder::setUpTitle()
{
	Loader* loader = Loader::getInstance();

	m_font = loader->loadFont("ASSETS/FONTS/nulshock.otf");


	m_title.setString(m_titleStr);
	m_title.setFont((*m_font));
	m_title.setFillColor(sf::Color::Black);
	m_title.setCharacterSize(Globals::SCREEN_WIDTH / SCALING);
	sf::FloatRect textSize = m_title.getLocalBounds();
	m_title.setOrigin(textSize.width / 2, textSize.height / 2);

	m_title.setPosition({ Globals::SCREEN_WIDTH / 2,  UI_HEIGHT_SCALING + 1 });
}

void UIScreenBorder::setUpTitleBox()
{
	sf::FloatRect textSize = m_title.getLocalBounds();

	m_titleBox = creatBoxForText(m_title);

	m_titleBox.setFillColor(m_lightBlue);
	m_titleBox.setOutlineThickness(5);
	m_titleBox.setOutlineColor(m_darkBlue);
	
}
