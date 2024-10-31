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

			sf::Vector2f closestPartPos = getClosestConnectionPos(partsConnector, m_position);

			std::cout << getClosestConnectionIndex(m_selectedPart->getConnectors(), closestPartPos) << std::endl;

			int selectedClosestPart = getClosestConnectionIndex(m_selectedPart->getConnectors(), closestPartPos);


			m_selectedPart->setPositionRelativeToConnectorPoint(closestPartPos, selectedClosestPart);

			m_selectedPart->m_body.setPosition(m_selectedPart->getPosition());

			// checking if this is valid
			if (m_selectedPart->m_body.getGlobalBounds().intersects(closestPart->m_body.getGlobalBounds()))
			{
				m_selectedPart->setPosition(m_position);
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

			std::cout << distance << std::endl;
			if (distance < 100)
			{
				return m_partsInScene[i];
			}
		}
	}

	return nullptr;
}

sf::Vector2f EditorMouse::getClosestConnectionPos(Connectors* t_connector, sf::Vector2f t_point)
{

	std::vector<sf::Vector2f> connectionPoints = t_connector->getAnchoredConnectionPoint();
	float shortestDistance = 150;
	sf::Vector2f closestConnection;

	for (int i = 0; i < connectionPoints.size(); i++)
	{
		// find point which is closest
		float distance = VectorMath::vectorLength(connectionPoints[i], t_point);

		if (distance < shortestDistance)
		{
			shortestDistance = distance;
			closestConnection = connectionPoints[i];
			
		}
	}

	return closestConnection;
}

int EditorMouse::getClosestConnectionIndex(Connectors* t_connector, sf::Vector2f t_point)
{
	std::vector<sf::Vector2f> connectionPoints = t_connector->getAnchoredConnectionPoint();
	float shortestDistance = 150;
	int closestConnection;

	for (int i = 0; i < connectionPoints.size(); i++)
	{
		// find point which is closest
		float distance = VectorMath::vectorLength(connectionPoints[i], t_point);

		if (distance < shortestDistance)
		{
			shortestDistance = distance;
			closestConnection=  i;
		}
	}
	
	return closestConnection;
}
