#pragma once
#include "UI.h"
#include "Globals.h"
#include "Loader.h"
#include "PartsLibarary.h"
#include <map>

class UIEditorBox : public UI
{
	public:

		UIEditorBox();

		void draw(sf::RenderWindow& t_window) override;

		void checkForInteraction(sf::Vector2f t_mousePosition) override;

		ShipPart* partSelectionCheck(sf::Vector2f t_mousePosition);
	private:

		void SetUpText();
		void setUpRect();
		void setUpButton();
		void setUpUiSprites();
		sf::RectangleShape m_uiBox;

		sf::CircleShape m_button;
		sf::CircleShape m_button2;

		sf::Text m_title;
		sf::Text m_text;
		sf::Font* m_font;

		std::vector<sf::Texture*> m_partTextures;


		PartType current = PartType::Hull;
		std::map<PartType, std::string> partTypeString = { {PartType::CockPit, "Cockpit" },
															{PartType::Hull,"Hull"},
															{PartType::Thruster, "Thruster"},
															{PartType::Left_Wing, "Left Wing" },
															{PartType::Right_Wing, "Right Wing"} };


		std::vector <std::vector<sf::Sprite>> m_uiSprites = { std::vector<sf::Sprite>(),
																std::vector<sf::Sprite>() ,
																std::vector<sf::Sprite>() ,
																std::vector<sf::Sprite>() ,
																std::vector<sf::Sprite>() };

};

