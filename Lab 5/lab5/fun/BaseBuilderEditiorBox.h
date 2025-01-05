#pragma once
#include "UIEditorBox.h"

class BaseBuilderEditiorBox : public UIEditorBox
{
	public :
	// Inherited via UIEditorBox
		void draw(sf::RenderWindow& t_window) override;
		void checkForInteraction(sf::Vector2f t_mousePosition) override;
		void updatePosition(sf::Vector2f t_position);
	private:
		void setUpUiSprites() override;

};

