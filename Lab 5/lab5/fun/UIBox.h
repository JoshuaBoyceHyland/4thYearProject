#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Loader.h"
#include "PartsLibarary.h"
#include <map>

class UIBox
{
	public:
		UIBox();
		void draw(sf::RenderWindow& t_window);
		void checkForButtonInteraction(sf::Vector2f t_mousePosition);

	private:

		void SetUpText();
		void setUpRect();
		void setUpButton();

		sf::Color m_lightBlue = sf::Color(21, 255, 255, 50);
		sf::Color m_darkBlue = sf::Color(14, 34, 99);
		sf::RectangleShape m_uiBox;

		sf::CircleShape m_button;
		sf::CircleShape m_button2;

		sf::Text m_title;
		sf::Text m_text;
		sf::Font* m_font;

		
		PartType current = PartType::Hull;
		std::map<PartType, std::string> partTypeString = { {PartType::CockPit, "Cockpit" },
															{PartType::Hull,"Hull"},
															{PartType::Thruster, "Thruster"},
															{PartType::Left_Wing, "Left Wing" },
															{PartType::Right_Wing, "Right Wing"} };
};

