#include "MiniMap.h"

MiniMap::MiniMap(sf::RenderWindow& t_window, GameObject* t_player, std::vector<GameObject*> t_icons) :
	m_window(t_window), 
	m_player(t_player)
{
	m_miniMapView.setSize(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);
	m_miniMapView.setViewport(sf::FloatRect(0.75f, 0.75f, 0.2f, 0.2f));

	m_border.setSize({ m_miniMapView.getViewport().width * m_window.getSize().x, m_miniMapView.getViewport().height * m_window.getSize().y });
	m_border.setOutlineColor(m_darkBlue);
	m_border.setFillColor(sf::Color::Transparent);
	m_border.setOutlineThickness(10.f);

	for (int i = 0; i < t_icons.size(); i++)
	{
		m_spriteIcons.emplace_back(t_icons[i]);
	}
}

void MiniMap::update()
{
	m_miniMapView.setCenter(m_player.m_spriteRef.getPosition());

	m_player.updateToReference();

	setPositionsOfWorldIcons();
	
	m_border.setPosition(m_miniMapView.getViewport().left * m_window.getSize().x, m_miniMapView.getViewport().top * m_window.getSize().y);
}

void MiniMap::drawContents()
{
	m_window.setView(m_miniMapView);


	m_window.draw(m_player.m_iconSprite);
	
	for (int i = 0; i < m_spriteIcons.size(); i++)
	{
		m_window.draw(m_spriteIcons[i].m_iconSprite);
	}
	
}

void MiniMap::drawBorder()
{
	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_border);
}

sf::Vector2f MiniMap::clampToEdge(sf::Vector2f t_objectPos, sf::Vector2f t_viewCenter, sf::Vector2f t_viewHalfSize)
{
	
	const float padding = 10.f;

	sf::Vector2f directionFromCenter = t_objectPos - t_viewCenter;

	float maxDistanceFromCenterX = t_viewHalfSize.x - padding;
	float maxDistanceFromCenterY = t_viewHalfSize.y - padding;

	// value for 
	float scaledX = 1.0f;
	float scaledY = 1.0f;

	if (directionFromCenter.x != 0)
	{
		scaledX = maxDistanceFromCenterX / std::abs(directionFromCenter.x);
	}
	if (directionFromCenter.y != 0)
	{
		scaledY = maxDistanceFromCenterY / std::abs(directionFromCenter.y);
	}


	float boundsScaler = std::min(1.f, std::min(scaledX, scaledY));

	sf::Vector2f clampedPosition = t_viewCenter + directionFromCenter * boundsScaler;


	return clampedPosition;
}
void MiniMap::setPositionsOfWorldIcons()
{
	for (int i = 0; i < m_spriteIcons.size(); i++)
	{
		sf::Vector2f viewHalfSize = m_miniMapView.getSize() / 2.f;

		float distanceFromCenterX = std::abs(m_spriteIcons[i].m_spriteRef.getPosition().x - m_miniMapView.getCenter().x);
		float distanceFromCenterY = std::abs(m_spriteIcons[i].m_spriteRef.getPosition().y - m_miniMapView.getCenter().y);
		// Calculate if base is outside the minimap view bounds

		if (distanceFromCenterX > viewHalfSize.x || distanceFromCenterY > viewHalfSize.y)
		{
			// Base is offscreen — clamp to minimap edge
			m_spriteIcons[i].m_iconSprite.setPosition(clampToEdge(m_spriteIcons[i].m_spriteRef.getPosition(), m_miniMapView.getCenter(), viewHalfSize));
		}
		else
		{
			// Base is within bounds — draw normally
			m_spriteIcons[i].m_iconSprite.setPosition(m_spriteIcons[i].m_spriteRef.getPosition());
		}
	}

}
