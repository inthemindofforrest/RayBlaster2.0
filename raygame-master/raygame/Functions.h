#pragma once
#include "raylib.h"
#include <string>
#include <time.h>

using namespace std;

class PLAYER;
class CONTROLS;
class BULLET;
class ENEMY;
class SETTINGS;
class CURRENCY;

class CONTROLS
{
public:

	int Up_Movement = KEY_W;
	int Down_Movement = KEY_S;
	int Right_Movement = KEY_D;
	int Left_Movement = KEY_A;

	int MainShoot = MOUSE_LEFT_BUTTON;
	int PauseGame = KEY_P;
};


class SETTINGS
{
public:
	enum {MouseControls, KeyboardControls};
	int ControllerType;

};


class BULLET
{
private:
	int Damage;
	int Speed;
	
	
	//Animations
	float AnimationTimer;
	float SpritePerFrame;
	int Frame;
	int TotalFrames;
	Texture2D Texture;


public:
	enum {_Player, _Enemy};
	int Target;
	Rectangle Rect;
	bool IsActive;
	void BulletHandler(float deltaTime, PLAYER Player);
	void BulletMovement(float deltaTime);
	void InitilizeBullet(PLAYER Player, int target, ENEMY Enemies, int speed);
	void DrawBullet(PLAYER Player);
	
};
class PLAYER
{
private:
	
	
	int MovementSpeed;
	int Coins;
	Rectangle Rect;
	//animations
	float AnimationTimer;
	float SpritePerFrame;
	int Frame;
	int TotalFrames;

	Texture2D Texture;

	float MoneyAnimationTimer;
	float MoneySpritePerFrame;
	int MoneyFrame;
	int MoneyTotalFrames;
	Texture2D MoneyTexture;
	
public:
	Color Shootcolor = PURPLE;
	int Health;
	int MaxHealth;
	SETTINGS Settings;
	CONTROLS Controls;
	void PlayerController(float deltaTime, BULLET * EnemyBullet, int SizeOfBullet);
	void MovePlayer(float deltaTime);
	void DrawPlayer();
	void InitilizePlayer();
	void SwapControls();
	void AddCoins(int Deposit);
	int GetCoins();
	void TakeCoins(int Withdrawl);
	void CollisionWithBullet(BULLET * PlayerBullets, int SizeOfBullets);
	int GetHealth();
	Vector2 GetPosition();
	Vector2 GetTexture();
};
class ENEMY
{
private:
	int EnemyType;
	int Health;
	int MovementSpeed;
	Rectangle Rect;
	Vector2 Origin;
	Vector2 Direction;

	//Animations
	float AnimationTimer;
	float SpritePerFrame;
	int Frame;
	int TotalFrames;

	Texture2D Texture;

public:
	float ShootTimer;
	bool IsAlive;
	enum {Basic_Enemy, Complex_Enemy, Boss_Enemy};
	void InitilizeEnemy(int Type);
	void DrawEnemy();
	void EnemyController(float deltaTime, BULLET * PlayerBullets, int SizeOfBullets, CURRENCY * Currency, int Size, int * CurrentEnemies);
	void MoveEnemy(float deltaTime);
	void CollisionWithBullet(BULLET * PlayerBullets, int SizeOfBullets);
	void CheckForDeath(CURRENCY * Currency, int Size, int * CurrentEnemies);

	Vector2 GetPosition();
	Vector2 GetTexture();
};
class CURRENCY
{
private:
	Texture2D Texture;
	float AnimationTimer;
	float SpritePerFrame;
	int Frame;
	int TotalFrames;
	int Speed;

public:
	Rectangle Rect;
	
	bool IsActive;

	void CurrencyHandler( PLAYER Player);
	void MoveCoin(PLAYER Player);
	void InstantiateCoin(Vector2 EnemyPosition);
	void DrawCoin();
	
};

class STAR
{
private:
	Vector2 Position;
	Texture2D ShootingStarTexture;
	float Radius;
	bool ShootingStar;
	bool Wished;
public:
	bool IsActive;
	void StarHandler(PLAYER * Player);
	void DrawStar(PLAYER * Player);
	void MoveStar();
	void InstantiateStar(STAR * Star, int SizeOfStars, int MinX, int MaxX);
	void InstantiateShootingStar(STAR * Star, int SizeOfStars, int MinX, int MaxX);
};
class MAINMENU
{
public:
	Texture2D PlayTexture;
	Texture2D OptionsTexture;
	Texture2D QuitTexture;
};

int MainMenuHandler(bool * IsMainMenu, int * MenuScreen, MAINMENU Menu, PLAYER * Player);
void CheckForPlayerDeath(PLAYER * Player, ENEMY * Enemies, int SizeOfEnemies,
	BULLET * Bullets, int SizeOfBullets, int * CurrentEnemies);
void BulletDeletion(BULLET * Bullets, int SizeOfBullet);
void EnemyBulletOrginizer(ENEMY * Enemies, int SizeOfEnemies, BULLET * bullet, int SizeOfBullets);
void CollectCoin(PLAYER * Player, CURRENCY * Currency, int SizeOfCurrency);
void SpawnCoin(Vector2 Position, CURRENCY * Currency, int CurrencySize);
void PlayerBulletOrginizer(PLAYER Player, BULLET * bullet, int SizeOfBullets);
void EnemyArrayOrginizer(ENEMY * enemies, int SizeOfEnemies, int *CurrentNumberOfEnemies, int MaxEnemies);
int RandomNumber(int Min, int Max);
void Animation(Vector2 Pos, int *Frame, int totalFrames,
	Texture2D texture, float * Timer, float TimePerFrame, Color color);