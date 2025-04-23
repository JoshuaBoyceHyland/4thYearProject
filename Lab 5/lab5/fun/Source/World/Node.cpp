#include "World/Node.h"


void Node::resetCosts()
{
	m_euclidian = -1;
	m_manhanttan = -1;
	m_cost = -1;


}

void Node::resetMarkings()
{
	m_marked = false;
	m_beingChecked = false;
	previous = nullptr;
}

bool Node::isWallNode()
{
	return m_neighbours.size() < 8;
}

