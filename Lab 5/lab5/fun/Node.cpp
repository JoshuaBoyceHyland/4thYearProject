#include "Node.h"


void Node::reset()
{
	m_euclidian = -1;
	m_manhanttan = -1;
	m_cost = -1;

	m_marked = false;
	m_beingChecked = false;
}
