#include "Editor/EditorMouse.h"

ShipEditorMouse::ShipEditorMouse()
{
}

void ShipEditorMouse::checkForOriginSelection()
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

void ShipEditorMouse::selectPiece(int t_index)
{
	m_selectedPart = m_partsInScene[t_index];
}

void ShipEditorMouse::checkForPartSelection()
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
					// disconnect from whatever other part they were connected to
					m_selectedPart->getConnectors()->connectionPoints[i].connectedTo->connectedTo = nullptr;
					m_selectedPart->getConnectors()->connectionPoints[i].connectedTo = nullptr;
				}
			}
			break;
		}
	}
	test = new ParticleSystem(m_position);
}

void ShipEditorMouse::releaseSelectedPart()
{
	if (m_selectedPart != nullptr)
	{

		ShipPart* closestPart = getClosestPart();

		// check if there is a part close enough to connect to
		if (closestPart != nullptr)
		{
			
			// get the closest part connection points
			Connector* partsConnector = closestPart->getConnectors();

			// get the closest connection point of the closest part which is closest to curretnly selected piece by the mouse
			sf::Vector2f closestConnectionPos = getClosestConnectionPos(partsConnector, m_position);

			std::cout << getClosestConnectionIndex(m_selectedPart->getConnectors(), closestConnectionPos) << std::endl;

			// check if our selected piece has a connection point close enough that is valid
			int selectedClosestConnectionPoint = getClosestConnectionIndex(m_selectedPart->getConnectors(), closestConnectionPos);

			// if valid
			if (selectedClosestConnectionPoint != -1)
			{
				
				m_selectedPart->setPositionRelativeToConnectorPoint(closestConnectionPos, selectedClosestConnectionPoint);

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

void ShipEditorMouse::update()
{
	if (m_selectedPart != nullptr)
	{
		m_selectedPart->setPosition(m_position);
	}

}

ShipPart* ShipEditorMouse::getClosestPart()
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

sf::Vector2f ShipEditorMouse::getClosestConnectionPos(Connector* t_connector, sf::Vector2f t_point)
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

int ShipEditorMouse::getClosestConnectionIndex(Connector* t_connector, sf::Vector2f t_point)
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
