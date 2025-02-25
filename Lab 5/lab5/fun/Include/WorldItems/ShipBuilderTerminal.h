#pragma once
#include <functional>
#include "WorldItems/WorldItem.h"
#include "Scenes/SceneTypes.h"

class PlayerInteractableItem : public WorldItem
{

	public:
		PlayerInteractableItem(Texture* t_texture, std::function<void(SceneType)> t_function);

		void use();


	private:

		SceneType m_targetScene = ShipEditor;
		std::function<void(SceneType)> m_function;
};

