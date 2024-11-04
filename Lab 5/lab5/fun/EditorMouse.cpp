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

			// need to check if this point is valid or else it will cl
			int selectedClosestPart = getClosestConnectionIndex(m_selectedPart->getConnectors(), closestPartPos);


			if (selectedClosestPart != -1)
			{

				m_selectedPart->setPositionRelativeToConnectorPoint(closestPartPos, selectedClosestPart);

				m_selectedPart->m_body.setPosition(m_selectedPart->getPosition());

				// checking if this is valid
				if (m_selectedPart->m_body.getGlobalBounds().intersects(closestPart->m_body.getGlobalBounds()))
				{
					m_selectedPart->setPosition(m_position);
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

	ShipPart* closestPart = nullptr;
	float closestDistance = 150;

	for (int i = 0; i < m_partsInScene.size(); i++)
	{
		if (m_selectedPart != m_partsInScene[i])
		{
			float distance = VectorMath::vectorLength(m_partsInScene[i]->getPosition(), m_position);

			std::cout << distance << std::endl;
			if (distance < closestDistance)
			{
				closestDistance = distance;
				closestPart = m_partsInScene[i];
			}
		}
	}

	return closestPart;
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
	int closestConnection = -1;

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
