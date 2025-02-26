#include "WorldItems/ShipBuilderTerminal.h"

PlayerInteractableItem::PlayerInteractableItem(Texture* t_texture, std::function<void(SceneType)> t_function ) :
	WorldItem( t_texture), 
	m_function( t_function)
{
	loadUIButton();
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



void PlayerInteractableItem::inRangeOfItem()
{
	m_drawUi = true;
	float hoverSpeed = 2.0f;
	float hoverRange = 5.0f;
	float elapsedTime = clock.getElapsedTime().asSeconds();
	float offsetY = std::sin(elapsedTime * hoverSpeed) * hoverRange;
	
	m_uiButton.setPosition(m_sprite.getPosition().x, originY + offsetY);
	m_uiText.setPosition(m_uiButton.getPosition());
}

void PlayerInteractableItem::reset()
{
	m_drawUi = false;
}

void PlayerInteractableItem::setTargetScene(SceneType t_target)
{
	m_targetScene = t_target;
}

void PlayerInteractableItem::setPosition(sf::Vector2f t_position)
{
	m_sprite.setPosition(t_position);
	m_uiButton.setPosition({ m_sprite.getPosition().x , m_sprite.getPosition().y - ( m_sprite.getTexture()->getSize().y * 1.5f) });

	originY = m_uiButton.getPosition().y;

	m_uiText.setPosition(m_uiButton.getPosition());
}

void PlayerInteractableItem::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
	if (m_drawUi)
	{
		t_window.draw(m_uiButton);
		t_window.draw(m_uiText);
	}
	
}

void PlayerInteractableItem::loadUIButton()
{
	Loader* loader = Loader::getInstance();
	m_uiTexture = loader->loadTexture("ASSETS/IMAGES/UI/Square Button_1.png");
	m_uiButton.setTexture(m_uiTexture->texture);
	m_uiButton.setScale(1.8, 1.8);
	m_uiButton.setOrigin(m_uiTexture->texture.getSize().x / 2, m_uiTexture->texture.getSize().y / 2);
	m_uiButton.setPosition(m_sprite.getPosition());
	

	m_uiText.setFont(*loader->loadFont("ASSETS/FONTS/nulshock.otf"));
	m_uiText.setString("E");
	m_uiText.setPosition(m_uiButton.getPosition());

	m_uiText.setCharacterSize(15);
	m_uiText.setOrigin(m_uiText.getLocalBounds().getSize().x / 2, m_uiText.getLocalBounds().getSize().y);



}
