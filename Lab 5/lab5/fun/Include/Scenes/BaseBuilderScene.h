#pragma once
#include "Scene.h"
#include "Globals.h"
#include "VectorMath.h"
#include "MovableCamera.h"
#include "Job.h"
#include "Room.h"
#include "Grid.h"
#include "BaseBuilderEditiorBox.h"
#include "TextureSplitter.h"
#include "Tile.h"
#include "MapSaver.h"
#include "Room.h"

class BaseBuilderScene : public Scene
{
	public:
		BaseBuilderScene(sf::RenderWindow& t_window);

		~BaseBuilderScene();

		// Inherited via Scene
		void update(sf::Time t_deltaTime) override;

		void render() override;

		void processKeys(sf::Event t_event) override;

		void processMousePress(sf::Event t_event) override;

		void processMouseRelease(sf::Event t_event) override;

		void processMouseMove(sf::Event t_event) override;

		void processMouseWheel(sf::Event t_event) override;

	private:

		sf::RectangleShape m_rect;
		MovableCamera m_camera;
		Grid* m_grid;
		BaseBuilderEditiorBox m_editorBox;
		Tile* m_selectedTiles = nullptr;
		MapSaver saver;
		Room m_room;
};

