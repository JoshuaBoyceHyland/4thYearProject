#include "raylib.h"
#include "raymath.h"  
#include "Globals.h"
#include <iostream>

const int NUM_WALLS = 4;

int main()
{
	InitWindow(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, "4th year project");

	// camera set up
	Camera camera = { 0 };
	camera.position = { 0.0f, 2.0f, 4.0f };
	camera.target = { 0.0f, 2.0f, 0.0f }; // point we are looking at;
	camera.up = { 0.0f, 1.0f, 0.0f };   // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;
	camera.projection = CAMERA_PERSPECTIVE; // projection type

	int currentCameraMode = CAMERA_FIRST_PERSON;

	Model firePit = LoadModel("Assets/Models/firepit.glb");
	

	float width = 6.0f; 
	float height = 0.2f;
	float z = 6;


	Mesh colliderMesh = GenMeshCube(width, height, z);
	Model colliders[4];

	Color col = RED;
	Model walls[4];
	Vector3 positions[4] = { {-15.9f, 0.0f, 0.0f}, { 0.0f, 0.0f, 15.9f}, { 15.9f, 0, 0} , { 0.0f, 0.0f, -15.9f} };
	Vector3 rotations[4] = { { 1.5708 * 3,0.0f, 1.5708 },  { 1.5708 * 3,0.0f, 1.5708  *2}, { 1.5708 * 3,0.0f, 1.5708 * 3 }, { 1.5708 * 3,0.0f, 1.5708 * 4} };

	for (int i = 0; i < NUM_WALLS; i++)
	{
		walls[i] = LoadModel("Assets/Models/wall.glb");

		walls[i].transform = MatrixRotateXYZ(rotations[i]);

		walls[i].transform = MatrixMultiply(MatrixScale(5.4, 1, 2), walls[i].transform);

		colliders[i] = LoadModelFromMesh(colliderMesh);
		colliders[i].transform = walls[i].transform;


	}

	
	//camera.

	DisableCursor(); // limit cursor to relative movement unsude window
	SetTargetFPS(60);

	// detects window being 
	while (!WindowShouldClose())
	{
		
		


		UpdateCamera(&camera, currentCameraMode);
		
		BeginDrawing();
		ClearBackground({68, 142, 226});
		BeginMode3D(camera);


		
		DrawPlane({ 0.0f, 0.0f, 0.0f }, { 32.0f, 32.0f }, DARKGREEN);

		for (int i = 0; i < NUM_WALLS; i++)
		{
			
			DrawModel(walls[i], positions[i], 1, LIGHTGRAY);

			DrawModelWires(colliders[i], positions[i], 1, col);
		}
		
		
		
		DrawModel(firePit, {0,0,0}, 1, LIGHTGRAY);
	
	

		EndMode3D();
		EndDrawing();
	}

}