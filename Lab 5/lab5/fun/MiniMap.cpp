#include "MiniMap.h"

MiniMap::MiniMap(sf::RenderWindow& t_window, GameObject* t_player, Grid** t_base) :
	m_window(t_window), 
	m_player(t_player), 
	m_base(t_base)
{
	m_miniMapView.setSize(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);
	m_miniMapView.setViewport(sf::FloatRect(0.75f, 0.75f, 0.2f, 0.2f));

	m_border.setSize({ m_miniMapView.getViewport().width * m_window.getSize().x, m_miniMapView.getViewport().height * m_window.getSize().y });
	m_border.setOutlineColor(m_darkBlue);
	m_border.setFillColor(sf::Color::Transparent);
	m_border.setOutlineThickness(10.f);

	loadSprites();
}

void MiniMap::update()
{
	m_miniMapView.setCenter(m_player->m_body.getPosition());


	m_playerSprite.setPosition(m_player->m_body.getPosition());
	m_playerSprite.setRotation(m_player->m_body.getRotation());

	m_baseSprite.setPosition((*m_base)->m_cells[0][0].m_body.getPosition());
	m_border.setPosition(m_miniMapView.getViewport().left * m_window.getSize().x, m_miniMapView.getViewport().top * m_window.getSize().y);
}

void MiniMap::drawContents()
{
	m_window.setView(m_miniMapView);


	m_window.draw(m_playerSprite);
	m_window.draw(m_baseSprite);
	
}

void MiniMap::drawBorder()
{
	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_border);
}

void MiniMap::loadSprites()
{
	Loader* loader = Loader::getInstance();

	Texture* playerShip = loader->loadTexture("ASSETS/IMAGES/Minimap/ship.png");
	Texture* base = loader->loadTexture("ASSETS/IMAGES/Minimap/home.png");

	m_playerSprite.setTexture(playerShip->texture);
	m_playerSprite.setOrigin({ playerShip->texture.getSize().x / 2.0f,playerShip->texture.getSize().y / 2.0f });

	m_baseSprite.setTexture(base->texture);
	m_baseSprite.setOrigin({ base->texture.getSize().x / 2.0f,base->texture.getSize().y / 2.0f });

}
