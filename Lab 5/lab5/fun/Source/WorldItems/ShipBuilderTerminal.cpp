#include "WorldItems/ShipBuilderTerminal.h"

PlayerInteractableItem::PlayerInteractableItem(Texture* t_texture, std::function<void(SceneType)> t_function ) :
	WorldItem( t_texture), 
	m_function( t_function)
{
}

void PlayerInteractableItem::use()
{
	if (m_function)
	{
		m_function(m_targetScene);
	}
	else
	{
		std::cout << "no owrky" << std::endl;
	}
	
}
