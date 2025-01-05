#include "BaseBuilderEditiorBox.h"

void BaseBuilderEditiorBox::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_uiBox);
	t_window.draw(m_title);
	t_window.draw(m_button);
	t_window.draw(m_button2);
}

void BaseBuilderEditiorBox::checkForInteraction(sf::Vector2f t_mousePosition)
{
}

void BaseBuilderEditiorBox::updatePosition(sf::Vector2f t_position)
{
	float outlineThickness = Globals::SCREEN_WIDTH / 100;
	m_uiBox.setPosition(t_position.x + outlineThickness, t_position.y +outlineThickness);
	m_button.setPosition({ m_uiBox.getPosition().x + m_uiBox.getSize().x - (Globals::SCREEN_WIDTH / 200), m_title.getPosition().y });
	m_button2.setPosition({ m_uiBox.getPosition().x + (Globals::SCREEN_WIDTH / 200)  , m_title.getPosition().y + 20 });
	m_title.setPosition({
							(m_uiBox.getPosition().x + (m_uiBox.getSize().x / 2))  /*- m_title.getCharacterSize() - Globals::SCREEN_WIDTH / SCALING*/,
							m_uiBox.getPosition().y + (Globals::SCREEN_WIDTH / 100)
		});
}

void BaseBuilderEditiorBox::setUpUiSprites()
{
}
