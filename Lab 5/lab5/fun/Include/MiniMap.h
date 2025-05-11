#pragma once
#include "Globals.h"
#include "Ship/Ship.h"
#include "World/Grid.h"

#include"SFMl/Graphics.hpp"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>



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
		m_iconSprite.setScale(0.5, 0.5);
	}


	void updateToReference()
	{
		m_iconSprite.setPosition(m_spriteRef.getPosition());
		m_iconSprite.setRotation(m_spriteRef.getRotation());
	}


	sf::Sprite m_iconSprite;
	sf::Sprite& m_spriteRef;
	std::map<Tag, std::string> texturePaths = { {Player_ship, "ASSETS/IMAGES/Minimap/ship.png"},
												{Player_Base, "ASSETS/IMAGES/Minimap/home.png"},
												{Enemy_Base, "ASSETS/IMAGES/Minimap/base.png"},
												{Player, "ASSETS/IMAGES/Minimap/player.png" },
												{Enemy, "ASSETS/IMAGES/Minimap/enemy.png" } };
};


class MiniMapGrid
{
	public:
		MiniMapGrid(Grid* t_grid)
		{
			// floor
			for (int i = 0; i < t_grid->m_traversableCells.size(); i++)
			{
				m_cells.push_back((*t_grid->m_traversableCells[i]));
				m_cells[i].m_body.setTexture(nullptr);
				m_cells[i].setColor(sf::Color(20, 20, 50));
		
			}

			// wallks
			for (int i = 0; i < t_grid->m_wallCells.size(); i++)
			{
				m_cells.push_back((*t_grid->m_wallCells[i]));
				m_cells[m_cells.size() - 1].m_body.setTexture(nullptr);
				m_cells[m_cells.size() - 1].setColor(sf::Color(90, 90, 120));

			}
		}

		void draw(sf::RenderWindow& t_window)
		{
			for (int i = 0; i < m_cells.size(); i++)
			{
				m_cells[i].draw(t_window);
			}
		}

		std::vector<Cell> m_cells;
};

class MiniMap
{
	public:
		MiniMap(sf::RenderWindow& t_window, float t_zoomFActor, GameObject* t_player, std::vector<GameObject*> t_icons, std::vector<Grid*> t_grids = {});

		void update();

		void drawBackground();
		void drawContents();

		void drawBorder();


		sf::View& getView() { return m_miniMapView; };

	private:

		sf::Vector2f clampToEdge(sf::Vector2f position, sf::Vector2f viewCenter, sf::Vector2f viewHalfSize);
		void setPositionsOfWorldIcons();

		sf::Color m_darkBlue = sf::Color(14, 34, 99);
		sf::Color m_lightBlue = sf::Color(209, 255, 255);
		
		sf::RectangleShape m_background;
		sf::RectangleShape m_border;

		sf::View m_miniMapView;
		sf::RenderWindow& m_window;

		MiniMapIcon m_player;
		
		std::vector<MiniMapGrid>m_grdOutlines;
		std::vector<MiniMapIcon> m_spriteIcons;

};

