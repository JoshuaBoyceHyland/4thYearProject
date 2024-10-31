#include "EditorMouse.h"

EditorMouse::EditorMouse()
{
}

void EditorMouse::checkForPartSelection()
{
	for ( int i = 0; i <m_partsInScene.size(); i++)
	{
		if (m_partsInScene[i]->m_body.getGlobalBounds().contains(m_position))
		{
			m_selectedPart = m_partsInScene[i];
			break;
		}
	}
}

void EditorMouse::releaseSelectedPart()
{
	if (m_selectedPart != nullptr)
	{

		ShipPart* closestPart = getClosestPart();

		if (closestPart != nullptr)
		{
			
			// get closests points connections
			Connectors* partsConnector = closestPart->getConnectors();

			getClosestConnection(partsConnector, m_position);
			
			std::vector<sf::Vector2f> connectionPoints = partsConnector->getAnchoredConnectionPoint();

			// go through the points 
			for (int i = 0; i < connectionPoints.size(); i++)
			{
				// find point which is closest
				float distance = VectorMath::vectorLength(connectionPoints[i], m_position);

				if (distance < 50)
				{
					m_selectedPart->setPosition(connectionPoints[i]);

					break;
				}
			}
		}

		m_selectedPart = nullptr;
	}


}

void EditorMouse::update()
{
	if (m_selectedPart != nullptr)
	{
		m_selectedPart->setPosition(m_position);
	}

}

ShipPart* EditorMouse::getClosestPart()
{

	for (int i = 0; i < m_partsInScene.size(); i++)
	{
		if (m_selectedPart != m_partsInScene[i])
		{
			float distance = VectorMath::vectorLength(m_partsInScene[i]->getPosition(), m_position);

			if (distance < 100)
			{
				return m_partsInScene[i];
			}
		}
	}

	return nullptr;
}

sf::Vector2f EditorMouse::getClosestConnection(Connectors* t_connector, sf::Vector2f t_point)
{

	std::vector<sf::Vector2f> connectionPoints = t_connector->getAnchoredConnectionPoint();

	for (int i = 0; i < connectionPoints.size(); i++)
	{
		// find point which is closest
		float distance = VectorMath::vectorLength(connectionPoints[i], m_position);

		if (distance < 50)
		{
			return connectionPoints[i];
		}
	}

}
