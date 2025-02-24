#pragma once
#include "Scene.h"
#include "Globals.h"
#include "MovableCamera.h"
#include "Job.h"
#include "World/Room.h"
#include "World/Grid.h"
#include "Editor/TileEditorBox.h"
#include "World/Tile.h"
#include "Utility/MapSaver.h"
#include "Utility/VectorMath.h"
#include "TextureSplitter.h"
#include "Librarys/RoomLibrary.h"

class RoomBuilderScene : public Scene
{
	public:
		RoomBuilderScene(sf::RenderWindow& t_window, std::function<void(SceneType)> t_sceneChangeFunction);

		~RoomBuilderScene();

		// Inherited via Scene
		void update(sf::Time t_deltaTime) override;

		void render() override;

		void processKeys(sf::Event t_event) override;

		void processMousePress(sf::Event t_event) override;

		void processMouseRelease(sf::Event t_event) override;

		void processMouseMove(sf::Event t_event) override;

		void processMouseWheel(sf::Event t_event) override;

	private:

		void setUpButton(std::function<void(SceneType)> t_sceneChangeFunction);

		sf::RectangleShape m_rect;
		MovableCamera m_camera;
		Grid* m_grid;
		EditorItem* m_selectedTiles = nullptr;
		TileEditorBox m_editorBox;
		
		MapSaver saver;
		Room* m_room;
		Button m_gameplayTransition;
};

