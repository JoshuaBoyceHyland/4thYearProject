#pragma once
#include "UI/UIEditorBox.h"
#include  "Librarys/TileLibrary.h"


class TileEditorBox : public UIEditorBox
{
	public :

		TileEditorBox();
	// Inherited via UIEditorBox
		void draw(sf::RenderWindow& t_window) override;
		

		void checkForInteraction(sf::Vector2f t_mousePosition) override;

		Tile* partSelectionCheck(sf::Vector2f t_mousePosition);

		bool contains(sf::Vector2f t_mousePosition);

		void updatePosition(sf::Vector2f t_position);

		void updateScale(float t_scale);

		
	private:

		void setUpUiSprites() override;

		TraversalProperty m_currentPart = TraversalProperty::Walkable;

		const int NUM_OF_SECTIONS = 3;

		std::map<TraversalProperty, std::string> propertyString = { {TraversalProperty::Walkable, "Walkable Tiles" },
																	{TraversalProperty::Unwalkable,"Unwalkable Tiles"},
																	{TraversalProperty::Job, "Job Tiles"},
																	 };

	
};

