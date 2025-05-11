#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
/// <summary>
/// Interface of UI
/// </summary>
class UI
{
	public:
		/// <summary>
		/// Derived UI will be draw in this function
		/// </summary>
		/// <param name="t_window"></param>
		virtual void draw(sf::RenderWindow& t_window) = 0;

		/// <summary>
		/// Derived UI will used this to check and handle UI interactions
		/// </summary>
		/// <param name="t_mousePosition"></param>
		virtual void checkForInteraction(sf::Vector2f t_mousePosition) = 0;
	protected:

		/// <summary>
		/// Creates a text box for the passed through piece of text
		/// </summary>
		/// <param name="t_text">Text the box will be made for</param>
		/// <returns>TextBox</returns>
		sf::ConvexShape creatBoxForText(sf::Text t_text);

		/// <summary>
		/// UI primary color
		/// </summary>
		sf::Color m_darkBlue = sf::Color(14, 34, 99);

		/// <summary>
		/// UI secondary Color
		/// </summary>
		sf::Color m_lightBlue = sf::Color(209, 255, 255);
		
		/// <summary>
		/// Value used to scale UI Width and Height
		/// </summary>
		const float SCALING = 100;

		/// <summary>
		/// Value used to proportion parts of UI to screen Width
		/// </summary>
		const float UI_WIDHT_SCALING = Globals::SCREEN_WIDTH / SCALING;

		/// <summary>
		/// Value used to proportion parts of UI to screen Height
		/// </summary>
		const float UI_HEIGHT_SCALING = Globals::SCREEN_WIDTH / SCALING;
};

