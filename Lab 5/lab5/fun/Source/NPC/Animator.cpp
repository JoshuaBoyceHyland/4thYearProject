#include "NPC/Animator.h"

Animator::Animator()
{
	Loader* loader = Loader::getInstance();
	
	m_animations.push_back(loader->loadAllTexturesInFile("ASSETS/IMAGES/NPC/1/Idle"));
	m_animations.push_back(loader->loadAllTexturesInFile("ASSETS/IMAGES/NPC/1/Run"));

	float spriteWidth = m_animations[0].m_sprites[0]->texture.getSize().x ;
	float spriteHeight = m_animations[0].m_sprites[0]->texture.getSize().y ;

	m_sprite.setTexture(m_animations[0].m_sprites[0]->texture);

	m_sprite.setOrigin({(float)20, (float)spriteHeight });
}

void Animator::animate()
{

	m_elapsedTime++;

	if (m_elapsedTime > m_elapseReset)
	{
		m_elapsedTime = 0;

		m_animations[m_currentState].m_currentFrame++;


		if (m_animations[m_currentState].m_currentFrame >= m_animations[m_currentState].m_maxFrames)
		{
			m_animations[m_currentState].m_currentFrame = 0;

		}
	}


	m_sprite.setTexture(m_animations[m_currentState].m_sprites[m_animations[m_currentState].m_currentFrame]->texture);
}
