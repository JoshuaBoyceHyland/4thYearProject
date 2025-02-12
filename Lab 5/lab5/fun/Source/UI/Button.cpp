#include "UI/Button.h"

Button::Button()
{
	loadFont();
	m_button = nullptr;
}

void Button::setText(std::string t_string)
{
	m_text.setString(t_string);
	scaleTextToBox();

}

void Button::setFunction(std::function<void(int)> t_function)
{
	m_function = t_function;
}

void Button::setShapeType(sf::Shape* t_shape)
{


	if (m_button != nullptr)
	{
		delete m_button;
		
	}
	
	m_button = t_shape;
}

void Button::scale(float t_scale)
{
	m_text.scale(t_scale, t_scale);
	m_button->scale(t_scale, t_scale);

}

sf::Shape* Button::getShape()
{
	return m_button;
}

void Button::loadFont()
{

	Loader* library = Loader::getInstance();

	m_font = library->loadFont("ASSETS/FONTS/nulshock.otf");
	m_text.setFont(*m_font);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(1.0f);

}

void Button::scaleTextToBox()
{
	float smallestDimesniion = std::min(m_text.getLocalBounds().width, m_text.getLocalBounds().height);

	m_text.setCharacterSize(smallestDimesniion);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition({ m_button->getPosition().x + (smallestDimesniion ),  m_button->getPosition().y });

}

void Button::checkForInteraction(sf::Vector2f t_position)
{
	if (m_button != nullptr)
	{
		if (m_button->getGlobalBounds().contains(t_position))
		{
			m_function(int(targetScene));
		}
	}

}

void Button::draw(sf::RenderWindow& t_window)
{
	t_window.draw(*m_button);
	t_window.draw(m_text);
	

}
