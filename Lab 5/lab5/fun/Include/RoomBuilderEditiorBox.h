#pragma once
#include "UIEditorBox.h"
#include "Room.h"

class RoomBuilderEditorBox : public UIEditorBox
{
	// Inherited via UIEditorBox
	public:
		void draw(sf::RenderWindow& t_window) override;
		void checkForInteraction(sf::Vector2f t_mousePosition) override;

		Room* roomSelectionCheck(sf::Vector2f t_mousePosition);

		void updatePosition(sf::Vector2f t_position);
		
		void updateScale(float t_scale);

	private:
		void setUpUiSprites() override;

		ResourceType m_currentPart = ResourceType::Electricty;
		const int NUM_OF_SECTIONS = 4;
		std::map<ResourceType, std::string> resourceString = {
																{ ResourceType::Electricty, "Electricity"},
																{ResourceType::Happinness, "Happinness"},
																{ResourceType::Water, "Water"},
																{ ResourceType::Oxygen, "Oxygen"}
																};
};