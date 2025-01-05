#pragma once
#include "UIEditorBox.h"

class ShipPartEditiorBox : public UIEditorBox
{
	ShipPartEditiorBox();

	ShipPart* partSelectionCheck(sf::Vector2f t_mousePosition);

	private:

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

