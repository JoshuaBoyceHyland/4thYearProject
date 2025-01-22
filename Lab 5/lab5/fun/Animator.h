#pragma once
#include <SFML/Graphics.hpp>
#include "Loader.h"

enum class SpriteDirection{ Left, Right, Top, Bottom};
class Animator
{

	public:
		Animator();


		sf::Sprite m_sprite;
	private:
		int numOfFrames = 4;
		
		sf::IntRect m_spriteDimension;
		std::vector<Texture*>m_spriteSheets;
	
};

