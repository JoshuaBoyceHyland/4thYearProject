#include "Animator.h"

Animator::Animator()
{
	Loader* loader = Loader::getInstance();
	m_spriteSheets = loader->loadAllTexturesInFile("ASSETS/IMAGES/NPC");

	float spriteWidth = m_spriteSheets[2]->texture.getSize().x / numOfFramesWidth;
	float spriteHeight = m_spriteSheets[2]->texture.getSize().y / numOfFramesHeight;

	m_spriteDimension.left = 0;
	m_spriteDimension.top = 0;
	m_spriteDimension.width = spriteWidth;
	m_spriteDimension.height = spriteHeight;

	m_sprite.setTexture(m_spriteSheets[2]->texture);
	m_sprite.setTextureRect(m_spriteDimension);
	m_sprite.setOrigin({(float)m_spriteDimension.width / 2, (float)spriteHeight });
}
