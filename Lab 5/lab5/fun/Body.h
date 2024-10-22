#pragma once
#include "Atttibutes.h"
class Body
{
	public:

		Body(std::string t_texturePath);
		Body(Attributes t_attributes, std::string t_texturePath);
		
		void draw(sf::RenderWindow& t_window);

	private:

		void setUpBody(std::string t_texturePath);

		sf::Texture m_texture;
		sf::RectangleShape m_body;
		

		Attributes m_attributes;
		std::vector<sf::CircleShape> m_connectionCircles;
};

