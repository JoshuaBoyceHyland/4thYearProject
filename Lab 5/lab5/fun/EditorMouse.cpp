#include "EditorMouse.h"

EditorMouse::EditorMouse()
{
}

void EditorMouse::checkForOriginSelection()
{
	for (int i = 0; i < m_partsInScene.size(); i++)
	{
		if (m_partsInScene[i]->m_body.getGlobalBounds().contains(m_position))
		{
			std::cout << "Selected" << std::endl;
			m_shipOrigin = m_partsInScene[i];
		}
	}
}

void EditorMouse::selectPiece(int t_index)
{
	m_selectedPart = m_partsInScene[t_index];
}

void EditorMouse::checkForPartSelection()
{
	for ( int i = 0; i <m_partsInScene.size(); i++)
	{
		if (m_partsInScene[i]->m_body.getGlobalBounds().contains(m_position))
		{
			selectPiece(i);
			for (int i = 0; i < m_selectedPart->getConnectors()->connectionPoints.size(); i++)
			{
				// check if we are connected to anything first
				if (m_selectedPart->getConnectors()->connectionPoints[i].connectedTo != nullptr)
				{
					m_selectedPart->getConnectors()->connectionPoints[i].connectedTo->connectedTo = nullptr;
					m_selectedPart->getConnectors()->connectionPoints[i].connectedTo = nullptr;
				}
			}
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
			Connector* partsConnector = closestPart->getConnectors();

			sf::Vector2f closestPartPos = getClosestConnectionPos(partsConnector, m_position);

			std::cout << getClosestConnectionIndex(m_selectedPart->getConnectors(), closestPartPos) << std::endl;

			// need to check if this point is valid or else it will cl
			int selectedClosestConnectionPoint = getClosestConnectionIndex(m_selectedPart->getConnectors(), closestPartPos);


			if (selectedClosestConnectionPoint != -1)
			{

				m_selectedPart->setPositionRelativeToConnectorPoint(closestPartPos, selectedClosestConnectionPoint);

				m_selectedPart->m_body.setPosition(m_selectedPart->getPosition());

				// checking if this is valid
				if (m_selectedPart->m_body.getGlobalBounds().intersects(closestPart->m_body.getGlobalBounds()))
				{
					m_selectedPart->setPosition(m_position);
				}
				else
				{
					// asssign they are connected to each other
					m_selectedPart->getConnectors()->connectionPoints[selectedClosestConnectionPoint].connectedTo = &closestPart->getConnectors()->connectionPoints[getClosestConnectionIndex(partsConnector, m_position)];
					m_selectedPart->getConnectors()->connectionPoints[selectedClosestConnectionPoint].connectedTo->connectedTo = &m_selectedPart->getConnectors()->connectionPoints[selectedClosestConnectionPoint];
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

sf::Vector2f EditorMouse::getClosestConnectionPos(Connector* t_connector, sf::Vector2f t_point)
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

int EditorMouse::getClosestConnectionIndex(Connector* t_connector, sf::Vector2f t_point)
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
