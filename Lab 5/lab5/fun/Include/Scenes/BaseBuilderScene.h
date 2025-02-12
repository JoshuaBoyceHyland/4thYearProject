#pragma once

#include "Scene.h"
#include "World/Grid.h"
#include "MovableCamera.h"
#include "Utility/MapSaver.h"
#include "Editor/RoomEditiorBox.h"

class BaseBuilderScene : public Scene
{
	public:
		// Inherited via Scene
		BaseBuilderScene(sf::RenderWindow& t_window, std::function<void(int)> t_sceneChangeFunction);
		void update(sf::Time t_deltaTime) override;
		void render() override;
		void processKeys(sf::Event t_event) override;
		void processMousePress(sf::Event t_event) override;
		void processMouseRelease(sf::Event t_event) override;
		void processMouseMove(sf::Event t_event) override;
		void processMouseWheel(sf::Event t_event) override;

	private:

		Room* m_room;
		Grid* m_grid;
		MapSaver saver;
		MovableCamera m_camera;
		RoomBuilderEditorBox m_editor;
		
};

