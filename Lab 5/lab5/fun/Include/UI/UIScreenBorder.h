#pragma once
#include "UI.h"
#include "Globals.h"
#include "Librarys/Loader.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class UIScreenBorder : public UI
{
	public:
		UIScreenBorder(std::string t_title);
		void draw(sf::RenderWindow& t_window) override;
		void checkForInteraction(sf::Vector2f t_mousePosition) override;


	private:

		void setUpBorder();
		void setUpTitle();
		void setUpTitleBox();
		
		sf::Font* m_font;
		sf::Text m_title;
		std::string m_titleStr;
		sf::RectangleShape m_border;
		sf::ConvexShape m_titleBox;
		


};

