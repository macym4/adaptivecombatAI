#include "raylib.h"
#include "main.hpp"
#include "VectorMath.hpp"

void visualize(jointChain chain) {
	const int screenWidth = 2000;
	const int screenHeight = 1000;

	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(screenWidth, screenHeight, "raylib - FABRIK Algorithm Visualization");

	for (std::size_t i = 0; i < chain.jointPositions.size(); ++i) {
		std::vector<double> joint = chain.jointPositions[i];
	}
	//	make point
	Vector2 targetPoint = { 60, 60 };

	bool moveTargetPoint = false;

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		Vector2 mouse = GetMousePosition();

		if (CheckCollisionPointCircle(mouse, targetPoint, 10.0f) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) moveTargetPoint = true;

		if (moveTargetPoint)
		{
			targetPoint = mouse;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) moveTargetPoint = false;
		}

		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("MOVE TARGET POINT WITH MOUSE", 15, 20, 20, GRAY);

		DrawCircleV(targetPoint, CheckCollisionPointCircle(mouse, targetPoint, 10.0f) ? 14.0f : 8.0f, moveTargetPoint ? RED : BLUE);

		EndDrawing();
		//----------------------------------------------------------------------------------

	// De-Initialization
	//--------------------------------------------------------------------------------------
		CloseWindow();        // Close window and OpenGL context
		//--------------------------------------------------------------------------------------

	}
};