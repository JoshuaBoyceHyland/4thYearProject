#include "MiniMap.h"

MiniMap::MiniMap(sf::RenderWindow& t_window, Ship* t_player, Grid** t_base) :
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
}

void MiniMap::update()
{
	m_miniMapView.setCenter(m_player->getPosition());

	m_border.setPosition(m_miniMapView.getViewport().left * m_window.getSize().x, m_miniMapView.getViewport().top * m_window.getSize().y);
}

void MiniMap::drawContents()
{
	m_window.setView(m_miniMapView);
	m_player->draw(m_window);

	if (m_base != nullptr)
	{
		(*m_base)->draw(m_window);
	}
	
}

void MiniMap::drawBorder()
{
	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_border);
}
