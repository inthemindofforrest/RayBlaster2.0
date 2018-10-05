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
#include "MainMenu.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Ray Blaster 2.0");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	int MaxEnemies = 10;
	int CurrentNumberOfEnemies = 0;

	float StarTimer = 0;
	int StarSet = 1;

	float ShootingStarTimer = 0;
	int NextShootingStar = 5;

	bool IsMainMenu = true;
	int MenuScreen = 0;

	PLAYER Player;
	ENEMY Enemies[100];
	BULLET Bullet[100];
	CURRENCY Currency[100];
	STAR Star[2000];
	STAR ShootingStar;
	MAINMENU Menu;
	srand(time(NULL));


	Player.InitilizePlayer();
	for (int i = 0; i < sizeof(Enemies) / sizeof(ENEMY); i++)
	{
		Enemies[i].InitilizeEnemy(Enemies->Basic_Enemy);
	}
	for (int i = 0; i < sizeof(Bullet) / sizeof(BULLET); i++)
	{
		Bullet[i].InitilizeBullet(Player, 0, Enemies[0], 250);
	}
	for (int i = 0; i < sizeof(Currency) / sizeof(CURRENCY); i++)
	{
		Currency[i].InstantiateCoin({0,0});
	}
	for (int i = 0; i < sizeof(Star) / sizeof(STAR); i++)
	{
		Star[i].InstantiateStar(Star, sizeof(Star) / sizeof(STAR), 0, GetScreenWidth());
	}
	ShootingStar.InstantiateShootingStar(&ShootingStar, 1, GetScreenWidth(), GetScreenWidth() + 1);

	Menu.PlayTexture = Menu.OptionsTexture = Menu.QuitTexture = LoadTexture("Button.png");

	Menu.PlayTexture.height *= 5;
	Menu.PlayTexture.width *= 7;
	Menu.OptionsTexture.height *= 5;
	Menu.OptionsTexture.width *= 7;
	Menu.QuitTexture.height *= 5;
	Menu.QuitTexture.width *= 7;

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{

		if (IsKeyPressed(KEY_P))
		{
			Player.SwapControls();
		}
		if (IsKeyDown(KEY_O))
		{
			IsMainMenu = true;
		}
		StarTimer += GetFrameTime();
		if(!IsMainMenu)
			ShootingStarTimer += GetFrameTime();
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);





		for (int i = 0; i < sizeof(Star) / sizeof(STAR); i++)
			if (Star[i].IsActive)
				Star[i].StarHandler(&Player);

		if (!IsMainMenu)
		{
			HideCursor();
			for (int i = 0; i < sizeof(Bullet) / sizeof(BULLET); i++)
				if (Bullet[i].IsActive)
					Bullet[i].BulletHandler(GetFrameTime(), Player);

			for (int i = 0; i < sizeof(Currency) / sizeof(CURRENCY); i++)
				if (Currency[i].IsActive)
					Currency[i].CurrencyHandler(Player);
			for (int i = 0; i < sizeof(Enemies) / sizeof(ENEMY); i++)
				if (Enemies[i].IsAlive)
				{
					Enemies[i].EnemyController(GetFrameTime(), Bullet,
						sizeof(Bullet) / sizeof(BULLET), Currency,
						sizeof(Currency) / sizeof(CURRENCY), &CurrentNumberOfEnemies);
					Enemies[i].ShootTimer += GetFrameTime();
				}


			
			if (ShootingStarTimer > NextShootingStar)
			{
				ShootingStar.InstantiateShootingStar(&ShootingStar, 1, GetScreenWidth(), GetScreenWidth() + 1);
				ShootingStar.IsActive = true;
				ShootingStarTimer = 0;
				NextShootingStar = RandomNumber(10, 20);
			}
			ShootingStar.StarHandler(&Player);
			PlayerBulletOrginizer(Player, Bullet, sizeof(Bullet) / sizeof(BULLET));
			EnemyArrayOrginizer(Enemies, sizeof(Enemies) / sizeof(ENEMY), &CurrentNumberOfEnemies, MaxEnemies);
			Player.PlayerController(GetFrameTime(), Bullet, sizeof(Bullet) / sizeof(BULLET));
			CollectCoin(&Player, Currency, sizeof(Currency) / sizeof(CURRENCY));
			EnemyBulletOrginizer(Enemies, sizeof(Enemies) / sizeof(ENEMY), Bullet, sizeof(Bullet) / sizeof(BULLET));
			BulletDeletion(Bullet, sizeof(Bullet) / sizeof(BULLET));
			CheckForPlayerDeath(&Player, Enemies, sizeof(Enemies) / sizeof(ENEMY),
				Bullet, sizeof(Bullet) / sizeof(BULLET), &CurrentNumberOfEnemies);
		}
		else if (IsMainMenu)
		{
			ShowCursor();
			if (MainMenuHandler(&IsMainMenu, &MenuScreen, Menu, &Player))
				return 1;
		}
		if (StarTimer > 1)
			{
				for (int i = 0; i < 100; i++)
				{
					if (!Star[i].IsActive)
					{
						Star[i * StarSet].InstantiateStar(Star, sizeof(Star) / sizeof(STAR), GetScreenWidth(), GetScreenWidth() + 10);
						StarSet++;
						Star[i * StarSet].IsActive = true;
						if (StarSet > 10)
							StarSet = 1;
					}
				}
				StarTimer = 0;
			}
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}