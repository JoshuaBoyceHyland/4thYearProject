#pragma once
#include "UI.h"
#include "Globals.h"
#include "Librarys/Loader.h"

#include "Button.h"

class UIEditorBox : public UI
{
	public:

		UIEditorBox();

		virtual void draw(sf::RenderWindow& t_window) = 0;

		virtual void checkForInteraction(sf::Vector2f t_mousePosition) = 0;

	protected:

		void SetUpText();
		void setUpRect();
		void setUpButton();

		virtual void setUpUiSprites() = 0;

		sf::RectangleShape m_uiBox;
		sf::CircleShape m_button;
		sf::CircleShape m_button2;
		
		sf::Text m_sceneChange;
		sf::Text m_title;
		sf::Text m_text;
		sf::Font* m_font;

		Button* button;

		std::vector<sf::Texture*> m_partTextures;

		std::vector <std::vector<sf::Sprite>> m_uiSprites; 

};

