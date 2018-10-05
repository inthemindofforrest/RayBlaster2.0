/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "Functions.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	HideCursor();

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	int MaxEnemies = 10;
	int CurrentNumberOfEnemies = 0;

	PLAYER Player;
	ENEMY Enemies[100];
	BULLET Bullet[100];
	CURRENCY Currency[100];



	Player.InitilizePlayer();
	for (int i = 0; i < sizeof(Enemies) / sizeof(ENEMY); i++)
	{
		Enemies[i].InitilizeEnemy(Enemies->Basic_Enemy);
	}
	for (int i = 0; i < sizeof(Bullet) / sizeof(BULLET); i++)
	{
		Bullet[i].InitilizeBullet(Player, 0, Enemies[0]);
	}
	for (int i = 0; i < sizeof(Currency) / sizeof(CURRENCY); i++)
	{
		Currency[i].InstantiateCoin({0,0});
	}

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{

		if (IsKeyPressed(KEY_P))
		{
			Player.SwapControls();
		}
		

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);


		for (int i = 0; i < sizeof(Enemies) / sizeof(ENEMY); i++)
			if (Enemies[i].IsAlive)
				Enemies[i].EnemyController(GetFrameTime(), Bullet, sizeof(Bullet) / sizeof(BULLET), Currency, sizeof(Currency)/sizeof(CURRENCY));

		for (int i = 0; i < sizeof(Bullet) / sizeof(BULLET); i++)
			if (Bullet[i].IsActive)
				Bullet[i].BulletHandler(GetFrameTime(), Player);

		for (int i = 0; i < sizeof(Currency) / sizeof(CURRENCY); i++)
			if (Currency[i].IsActive)
				Currency[i].CurrencyHandler(Player);

		PlayerBulletOrginizer(Player, Bullet, sizeof(Bullet) / sizeof(BULLET));
		EnemyArrayOrginizer(Enemies, sizeof(Enemies) / sizeof(ENEMY), &CurrentNumberOfEnemies, MaxEnemies);
		Player.PlayerController(GetFrameTime());
		CollectCoin(&Player, Currency, sizeof(Currency) / sizeof(CURRENCY));



		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}