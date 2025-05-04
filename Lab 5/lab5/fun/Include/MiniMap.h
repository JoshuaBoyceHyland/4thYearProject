#pragma once
#include "Globals.h"
#include "Ship/Ship.h"
#include "World/Grid.h"

#include"SFMl/Graphics.hpp"




class MiniMapIcon 
{
public:
	MiniMapIcon(GameObject* t_gameObject) : m_spriteRef(t_gameObject->m_body)
	{
		Loader* loader = Loader::getInstance();
		Texture* texture = loader->loadTexture(texturePaths[t_gameObject->m_tag]);
		m_iconSprite.setTexture(texture->texture);
		m_iconSprite.setOrigin({ texture->texture.getSize().x / 2.0f,texture->texture.getSize().y / 2.0f });
		m_iconSprite.setPosition(m_spriteRef.getPosition());
		m_iconSprite.setRotation(m_spriteRef.getRotation());
	}


	void updateToReference()
	{
		m_iconSprite.setPosition(m_spriteRef.getPosition());
		m_iconSprite.setRotation(m_spriteRef.getRotation());
	}


	sf::Sprite m_iconSprite;
	sf::Sprite& m_spriteRef;
	std::map<Tag, std::string> texturePaths = { {Player_ship, "ASSETS/IMAGES/Minimap/ship.png"},
												{Player_Base, "ASSETS/IMAGES/Minimap/home.png"} };
};

class MiniMap
{
	public:
		MiniMap(sf::RenderWindow& t_window, GameObject* t_player, std::vector<GameObject*> t_icons);

		void update();

		void drawContents();

		void drawBorder();


		sf::View& getView() { return m_miniMapView; };

	private:

		sf::Vector2f clampToEdge(sf::Vector2f position, sf::Vector2f viewCenter, sf::Vector2f viewHalfSize);
		void setPositionsOfWorldIcons();

		sf::Color m_darkBlue = sf::Color(14, 34, 99);
		sf::Color m_lightBlue = sf::Color(209, 255, 255);
		sf::RectangleShape m_border;

		sf::View m_miniMapView;
		sf::RenderWindow& m_window;

		MiniMapIcon m_player;
	
		std::vector<MiniMapIcon> m_spriteIcons;

};

