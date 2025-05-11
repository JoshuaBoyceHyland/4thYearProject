#pragma once
#include "UI/UIEditorBox.h"
#include "PartsLibarary.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class ShipPartEditiorBox : public UIEditorBox
{

	public: 
		ShipPartEditiorBox();

		void draw(sf::RenderWindow& t_window) override;

		void checkForInteraction(sf::Vector2f t_mousePosition) override;

		ShipPart* partSelectionCheck(sf::Vector2f t_mousePosition);
		
	private:

		void setUpUiSprites() override;

		PartType m_currentPart = PartType::Hull;

		const int NUM_OF_SECTIONS = 5;

		
		
		/// <summary>
		/// Paps part type to a string
		/// </summary>
		std::map<PartType, std::string> partTypeString = { {PartType::CockPit, "Cockpit" },
																	{PartType::Hull,"Hull"},
																	{PartType::Thruster, "Thruster"},
																	{PartType::Left_Wing, "Left Wing" },
																	{PartType::Right_Wing, "Right Wing"} };
};

