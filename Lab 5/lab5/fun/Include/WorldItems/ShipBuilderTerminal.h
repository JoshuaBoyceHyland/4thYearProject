#pragma once
#include <functional>
#include "WorldItems/WorldItem.h"
#include "Scenes/SceneTypes.h"

class PlayerInteractableItem : public WorldItem
{

	public:
		PlayerInteractableItem(Texture* t_texture, std::function<void(SceneType)> t_function);

		void use();

		void inRangeOfItem();

		void reset();

		void setPosition(sf::Vector2f t_position) override;

		void draw(sf::RenderWindow& t_window) override;

	private:
		void loadUIButton();

		bool m_drawUi = false;

		float originY = 0;
		Texture* m_uiTexture;
		sf::Text m_uiText;
		sf::Sprite m_uiButton;
		SceneType m_targetScene = ShipEditor;
		std::function<void(SceneType)> m_function;
		sf::Clock clock;
		
};

