#pragma once
#include "Scene.h"
#include "Editor/EditorMouse.h"
#include "Ship/PartsLibarary.h"
#include "UI/UIScreenBorder.h"
#include "Ship/ShipPartEditiorBox.h"
#include "Ship/Ship.h"
#include "Utility/MapSaver.h"
/// <summary>
/// Class for
/// </summary>
class ShipEditorScene : public Scene
{
	public:

		/// <summary>
		/// constructor for Editor scene
		/// Updates the mouses vector of scene parts
		/// </summary>
		/// <param name="t_window">Assigns to our reference so we can draw to the main window</param>
		ShipEditorScene(sf::RenderWindow& t_window );

		/// <summary>
		/// Editor Scene deconstructor, deletes parts and saves created ship
		/// </summary>
		~ShipEditorScene();

		/// <summary>
		/// Updates our objects in the scene
		/// </summary>
		/// <param name="t_deltaTime"></param>
		virtual void update(sf::Time t_deltaTime) override;

		/// <summary>
		/// Renders all objects
		/// </summary>
		virtual void render() override;

		/// <summary>
		/// Handles Key presses
		/// </summary>
		/// <param name="t_event">Key Press Event</param>
		virtual void processKeys(sf::Event t_event) override;

		/// <summary>
		/// Handles what to do with on mouse press
		/// </summary>
		/// <param name="t_event">Mouse Press Event</param>
		virtual void processMousePress(sf::Event t_event) override;

		/// <summary>
		/// Handles what to do with mouse release event
		/// </summary>
		/// <param name="t_event">Mouse release event</param>
		virtual void processMouseRelease(sf::Event t_event) override;

		/// <summary>
		/// Handles what to do withe a mouse move event
		/// </summary>
		/// <param name="t_event">Mouse move event</param>
		virtual void processMouseMove(sf::Event t_event) override;

		// Inherited via Scene
		void processMouseWheel(sf::Event t_event) override;

		/// <summary>
		/// Returns the ship the player created
		/// </summary>
		/// <returns></returns>
		Ship getCreatedShip();

	private: 

		void saveCreatedShip();

		ShipPart* m_origin = nullptr;

		/// <summary>
		/// Vector of all parts in the scene
		/// </summary>
		std::vector<ShipPart*> m_parts; 
		/// <summary>
		/// Editor mouse for the scene
		/// </summary>
		ShipEditorMouse m_mouse;
		/// <summary>
		///  Ui for this scene
		/// </summary>
		ShipPartEditiorBox m_ui;

		UIScreenBorder m_uiBorder;

		PlayerDataLoader saver;
		



};

