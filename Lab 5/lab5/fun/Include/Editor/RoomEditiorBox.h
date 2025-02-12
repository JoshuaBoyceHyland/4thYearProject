#pragma once
#include "UI/UIEditorBox.h"
#include "Librarys/RoomLibrary.h"

class RoomBuilderEditorBox : public UIEditorBox
{
	// Inherited via UIEditorBox
	public:
		RoomBuilderEditorBox();
		

		void draw(sf::RenderWindow& t_window) override;

		void checkForInteraction(sf::Vector2f t_mousePosition) override;

		Room* roomSelectionCheck(sf::Vector2f t_mousePosition);

		bool contains(sf::Vector2f t_mousePosition);

		void updatePosition(sf::Vector2f t_position);
		
		void updateScale(float t_scale);
		
		

	private:
		void setUpUiSprites() override;

		
		const int NUM_OF_SECTIONS = 4;


		ResourceType m_currentPart = ResourceType::Electricty;
		
		std::map< ResourceType, std::vector<Grid>> m_uiRooms;

		std::map<ResourceType, std::string> resourceString = {
																{ ResourceType::Electricty, "Electricity"},
																{ResourceType::Happinness, "Happinness"},
																{ResourceType::Water, "Water"},
																{ ResourceType::Oxygen, "Oxygen"}
																};
};