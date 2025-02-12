#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Librarys/Loader.h"
#include "Scenes/SceneTypes.h"

class Button
{
	public:
		Button();

		void setText(std::string t_string);

		void setFunction(std::function<void(int)> t_function);

		void setShapeType(sf::Shape* t_shape);

		void scale(float t_scale);

		void checkForInteraction(sf::Vector2f t_position);

		void draw(sf::RenderWindow& t_window);

		sf::Shape* getShape();

	protected:
		void loadFont();

		void scaleTextToBox();

		sf::Font* m_font;
		sf::Text m_text;
		sf::Shape* m_button = nullptr;
		SceneType targetScene = SceneType::Menu;
		std::function<void(int)> m_function;

};

