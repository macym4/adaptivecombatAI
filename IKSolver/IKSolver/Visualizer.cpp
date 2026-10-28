#include "raylib.h"
#include "main.hpp"
#include "VectorMath.hpp"

void visualize(jointChain chain) {
	const int screenWidth = 2000;
	const int screenHeight = 1000;

	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(screenWidth, screenHeight, "raylib - FABRIK Algorithm Visualization");

	Camera3D camera = { 0 };
	camera.position = Vector3 { 0.0f, 10.0f, 10.0f };  // Camera position
	camera.target =  Vector3 { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up =  Vector3 { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };


	//	make point
	Vector3 targetSphere = { 4.0f, 0.0f, 0.0f };
	float targetSphereSize = 1.5f;

	bool moveTargetSphere = false;

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{

		// Moving the target point
		if (IsKeyDown(KEY_RIGHT)) targetSphere.x += 0.2f;
		else if (IsKeyDown(KEY_LEFT)) targetSphere.x -= 0.2f;
		else if (IsKeyDown(KEY_DOWN)) targetSphere.z += 0.2f;
		else if (IsKeyDown(KEY_UP)) targetSphere.z -= 0.2f;
		else if (IsKeyDown(KEY_PERIOD)) targetSphere.y -= 0.2f;
		else if (IsKeyDown(KEY_COMMA)) targetSphere.y += 0.2f;


		// Moving the camera
		if (IsKeyDown(KEY_W)) camera.position.x += 0.2f;
		else if (IsKeyDown(KEY_S)) camera.position.x -= 0.2f;
		else if (IsKeyDown(KEY_W)) camera.position.z += 0.2f;
		else if (IsKeyDown(KEY_D)) camera.position.z -= 0.2f;
		else if (IsKeyDown(KEY_E)) camera.position.y -= 0.2f;
		else if (IsKeyDown(KEY_Q)) camera.position.y += 0.2f;

		// Make target into solver format
		std::vector<double> solverTarget = {
			targetSphere.x,
			targetSphere.y,
			targetSphere.z
		};

		// recalculate FABRIK
		chain.calculateNewPositions(solverTarget);


		// Update
		//----------------------------------------------------------------------------------
		Vector2 mouse = GetMousePosition();


		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		DrawSphere(targetSphere, 0.2f, BLUE);

		// Make the joints and bones between the joints
		for (std::size_t i = 0; i < chain.jointPositions.size(); ++i) {

			const auto& joint = chain.jointPositions[i];

			Vector3 position = {
				static_cast<float>(joint[0]),
				static_cast<float>(joint[1]),
				static_cast<float>(joint[2])
			};

			DrawSphere(position, 0.1f, RED);

			if (i > 0) {
				const auto& previousJoint = chain.jointPositions[i - 1];

				Vector3 previousPosition = {
					static_cast<float>(previousJoint[0]),
					static_cast<float>(previousJoint[1]),
					static_cast<float>(previousJoint[2])
				};

				DrawLine3D(previousPosition, position, BLUE);
			}
		}

		DrawGrid(100, 1.0f);

		EndMode3D();

		DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);
		DrawText("Move the target point with your mouse.", 15, 20, 20, GRAY);

		DrawFPS(10, 10);

	//	for (int i = 1; i < chain.jointPositions.size(); i++)
	//	{
	//		DrawLineEx(chain.jointPositions[i], chain.jointPositions[i - 1], thick, ColorFromHSV(((float)i / strokeCount) * 360.0f, 1.0f, 1.0f));
	//	}
	//}

		EndDrawing();
		//----------------------------------------------------------------------------------

	// De-Initialization
	//--------------------------------------------------------------------------------------
		CloseWindow();        // Close window and OpenGL context
		//--------------------------------------------------------------------------------------

	}
};

//Vector3 makeBone(x, y, z, size, thickness, color = red) {
//
//
//}
//
//Vector3 makeSphere(x, y, z, size, thickness, color = orange) {
//	//	make point
//	Vector3 targetSphere = { 4.0f, 0.0f, 0.0f };
//	float targetSphereSize = 1.5f;
//
//}