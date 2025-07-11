#pragma once
#include "UI/UIEditorBox.h"
#include  "Librarys/TileLibrary.h"
#include  "Librarys/WorldItemLibrary.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class TileEditorBox : public UIEditorBox
{
	public :

		TileEditorBox();
	// Inherited via UIEditorBox
		void draw(sf::RenderWindow& t_window) override;
		

		void checkForInteraction(sf::Vector2f t_mousePosition) override;

		EditorItem* partSelectionCheck(sf::Vector2f t_mousePosition);

		bool contains(sf::Vector2f t_mousePosition);

		void updatePosition(sf::Vector2f t_position);

		void updateScale(float t_scale);

		TraversalProperty m_currentPart = TraversalProperty::Walkable;

	private:

		void setUpUiSprites() override;


		

		const int NUM_OF_SECTIONS = 3;

		std::map<TraversalProperty, std::string> propertyString = { {TraversalProperty::Walkable, "Walkable Tiles" },
																	{TraversalProperty::Unwalkable,"Unwalkable Tiles"}, 
																	{TraversalProperty::Job,"World Items"}
																	 };

	
};

