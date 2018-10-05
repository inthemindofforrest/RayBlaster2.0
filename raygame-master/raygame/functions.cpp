#include "Functions.h"


//Player

void PLAYER::PlayerController(float deltaTime, BULLET * EnemyBullet, int SizeOfBullet)
{
	MovePlayer(deltaTime);
	DrawPlayer();
	CollisionWithBullet(EnemyBullet, SizeOfBullet);
}
void PLAYER::MovePlayer(float deltaTime)
{
	if (Settings.ControllerType == Settings.KeyboardControls)
	{
		if (IsKeyDown(Controls.Up_Movement) && Rect.y >= 10)
		{
			Rect.y -= MovementSpeed * (deltaTime);
		}
		if (IsKeyDown(Controls.Down_Movement) && Rect.y <= (GetScreenHeight() - 10 - (Texture.height)))
		{
			Rect.y += MovementSpeed * (deltaTime);
		}
		if (IsKeyDown(Controls.Right_Movement) && Rect.x <= (GetScreenWidth() / 5) * 2  - (Texture.width / TotalFrames))
		{
			Rect.x += MovementSpeed * (deltaTime);
		}
		if (IsKeyDown(Controls.Left_Movement) && Rect.x >= 10)
		{
			Rect.x -= MovementSpeed * (deltaTime);
		}
	}
	else if(Settings.ControllerType == Settings.MouseControls)
	{
		

		if (GetMouseX() < 10 + (Texture.width / 3) / 2)
		{
			SetMousePosition({ 10 + (float)(Texture.width / 3) / 2, (float)GetMouseY() });
		}
		if (GetMouseY() < 10 + Texture.height / 2)
		{
			SetMousePosition({ (float)GetMouseX(), 10 + (float)Texture.height / 2 });
		}
		if (GetMouseY() > (GetScreenHeight() - 10 - (Texture.height / 2)))
		{
			SetMousePosition({ (float)GetMouseX(), (float)(GetScreenHeight() - 10 - (Texture.height / 2)) });
		}
		if (GetMouseX() > ((GetScreenWidth() / 5) * 2 - (Texture.width / TotalFrames)))
		{
			SetMousePosition({ (float)(GetScreenWidth() / 5) * 2 - (Texture.width / TotalFrames), (float)GetMouseY() });
		}

		if (Rect.x < 10 + (Texture.width / 3) / 2)
		{
			Rect.x = 10 + (float)(Texture.width / 3) / 2;
		}
		if (Rect.y < 10 + (float)Texture.height / 2)
		{
			Rect.y = 10 + Texture.height / 2;
		}
		if (Rect.x >((GetScreenWidth() / 5) * 2 - (Texture.width / TotalFrames)))
		{
			Rect.x = ((GetScreenWidth() / 5) * 2 - (Texture.width));
		}
		if (Rect.y > (GetScreenHeight() - 10 - (Texture.height / 2)))
		{
			Rect.y = (GetScreenHeight() - 10 - (Texture.height / 2));
		}
		Rect.x = GetMouseX() - (Texture.width / TotalFrames) / 2;
		Rect.y = GetMouseY() - (Texture.height) / 2;
	}
}
void PLAYER::DrawPlayer()
{
	Animation({ Rect.x, Rect.y }, &Frame, TotalFrames, Texture, &AnimationTimer, SpritePerFrame, WHITE);
	DrawText(to_string(Coins).c_str(), ((float)GetScreenWidth() / 7) * 6, ((float)GetScreenHeight() / 20), 20, BLUE);
	Animation({ ((float)GetScreenWidth() / 7) * 6 - 30, ((float)GetScreenHeight() / 20) }, &MoneyFrame, MoneyTotalFrames, MoneyTexture, &MoneyAnimationTimer, MoneySpritePerFrame, WHITE);
	for (int i = 0; i < Health; i++)
	{
		DrawRectangle((i * 20) + 20, (GetScreenHeight() / 20) * 1, 10, 10, RED);
	}

}
void PLAYER::InitilizePlayer()
{
	Health = 3;
	MaxHealth = 3;
	MovementSpeed = 250;
	//Settings.ControllerType = Settings.KeyboardControls;
	Settings.ControllerType = Settings.MouseControls;

	Texture = LoadTexture("Rocket.png");
	MoneyTexture = LoadTexture("Currency.png");
	Rect = { 100,100,(float)Texture.width / 3,(float)Texture.height };
	AnimationTimer = 0;
	SpritePerFrame = .1f;
	Frame = 1;
	TotalFrames = 3;

	MoneyAnimationTimer = 0;
	MoneySpritePerFrame = .2f;
	MoneyFrame = 1;
	MoneyTotalFrames = 3;
	Coins = 0;
}
void PLAYER::SwapControls()
{

	switch (Settings.ControllerType)
	{
	case 0:
		Settings.ControllerType = Settings.KeyboardControls;
		break;
	case 1:
		Settings.ControllerType = Settings.MouseControls;
		break;
	default:
		break;
	}
}
void PLAYER::AddCoins(int Deposit)
{
	Coins += Deposit;
}
int PLAYER::GetCoins()
{
	return Coins;
}
void PLAYER::TakeCoins(int Withdrawl)
{
	Coins -= Withdrawl;
}
void PLAYER::CollisionWithBullet(BULLET * EnemyBullet, int SizeOfBullets)
{
	for (int i = 0; i < SizeOfBullets; i++)
		if (EnemyBullet[i].IsActive)
			if (CheckCollisionRecs(Rect, EnemyBullet[i].Rect) && EnemyBullet[i].Target == 0)
			{
				Health--;
				EnemyBullet[i].IsActive = false;
			}
}
int PLAYER::GetHealth()
{
	return Health;
}

Vector2 PLAYER::GetPosition()
{
	return { Rect.x, Rect.y };
}
Vector2 PLAYER::GetTexture()
{
	return { (float)Texture.width, (float)Texture.height };
}


//Enemy

void ENEMY::EnemyController(float deltaTime, BULLET * PlayerBullets, int SizeOfBullets, 
	CURRENCY * Currency, int Size, int * CurrentEnemies)
{
	DrawEnemy();
	MoveEnemy(deltaTime);
	CollisionWithBullet(PlayerBullets, SizeOfBullets);
	CheckForDeath(Currency, Size, CurrentEnemies);
}
void ENEMY::DrawEnemy()
{
	if (IsAlive)
	{
		Animation({ Rect.x, Rect.y }, &Frame, TotalFrames, Texture, &AnimationTimer, SpritePerFrame, WHITE);
		DrawText(to_string(Health).c_str(), Rect.x + ((Texture.width / 3) / 2) - 2, Rect.y - 15, 16, WHITE);
	}
}
void ENEMY::InitilizeEnemy(int Type)
{
	EnemyType = Type;
	Health = 3;
	MovementSpeed = RandomNumber(100,200);
	Texture = LoadTexture("Alien.png");
	Origin = { (float)RandomNumber((float)((GetScreenWidth() / 5) * 3) - (float)(Texture.width / 3),(float)((GetScreenWidth()) - (float)(Texture.width / 3))),   
		(float)RandomNumber(0 + (float)(Texture.height),(float)((GetScreenHeight()) - (float)(Texture.height))) };
	Rect = { Origin.x, Origin.y, (float)Texture.width / 3,(float)Texture.height };
	IsAlive = false;
	AnimationTimer = 0;
	SpritePerFrame = .1f;
	Frame = 1;
	TotalFrames = 3;
	Direction = { 1,1 };
	ShootTimer = RandomNumber(2,4);
}
void ENEMY::MoveEnemy(float deltaTime)
{
	Rect.y += MovementSpeed * deltaTime * Direction.y;
	Rect.x += MovementSpeed * deltaTime * Direction.x;
	if (Direction.y >= 0 && Rect.y >= Origin.y + RandomNumber(15,30))
	{
		Direction.y = -1 * (float)RandomNumber(1,10) / 10;
	}
	if (( Direction.y < 0) && Rect.y <= Origin.y - RandomNumber(15, 30))
	{
		Direction.y = (float)RandomNumber(1, 10) / 10;
	}
	if ( Direction.x >= 0 && Rect.x >= Origin.x + RandomNumber(15, 30))
	{
		Direction.x = -1 * (float)RandomNumber(1, 10) / 10;
	}
	if ((Direction.x < 0) && Rect.x <= Origin.x - RandomNumber(15, 30))
	{
		Direction.x = (float)RandomNumber(1, 10) / 10;
	}
	
}
void ENEMY::CollisionWithBullet(BULLET * PlayerBullets, int SizeOfBullets)
{
	for(int i = 0; i < SizeOfBullets; i++)
		if(PlayerBullets[i].IsActive)
			if (CheckCollisionRecs(Rect, PlayerBullets[i].Rect) && PlayerBullets[i].Target == 1)
			{
				Health--;
				PlayerBullets[i].IsActive = false;
			}
}
void ENEMY::CheckForDeath(CURRENCY * Currency, int Size, int * CurrentEnemies)
{
	if (Health <= 0)
	{
		IsAlive = false;
		SpawnCoin({ Rect.x, Rect.y }, Currency, Size);
		(*CurrentEnemies)--;
	}
}
Vector2 ENEMY::GetPosition()
{
	return { Rect.x, Rect.y };
}
Vector2 ENEMY::GetTexture()
{
	return { (float)Texture.width, (float)Texture.height };
}

//Bullets
void BULLET::BulletHandler(float deltaTime, PLAYER Player)
{
	DrawBullet(Player);
	BulletMovement(deltaTime);
}
void BULLET::BulletMovement(float deltaTime)
{
		Rect.x += Speed * deltaTime;
}
void BULLET::DrawBullet(PLAYER Player)
{
	if (IsActive)
		if (Target == 0)
			Animation({ Rect.x, Rect.y }, &Frame, TotalFrames, Texture, &AnimationTimer, SpritePerFrame, GREEN);
		else if (Target == 1)
			Animation({ Rect.x, Rect.y }, &Frame, TotalFrames, Texture, &AnimationTimer, SpritePerFrame, Player.Shootcolor);
}
void BULLET::InitilizeBullet(PLAYER Player, int target, ENEMY Enemies, int speed)
{
	Damage = 1;
	Texture = LoadTexture("Bullet.png");
	Frame = 1;
	TotalFrames = 3;
	AnimationTimer = 0;
	SpritePerFrame = .1f;
	Speed = speed;
	Target = target;
	if (Target == 1)
	{
		Rect = { Player.GetPosition().x, Player.GetPosition().y, (float)Texture.width / 3, (float)Texture.height };
	
	}

	if (Target == 0)
	{
		Rect = { Enemies.GetPosition().x, Enemies.GetPosition().y, (float)Texture.width / 3, (float)Texture.height };
		Speed *= -1;
	}

	IsActive = false;
}

//Coins
void CURRENCY::CurrencyHandler(PLAYER Player)
{
	if (IsActive)
	{
		MoveCoin(Player);
		DrawCoin();
	}
}
void CURRENCY::InstantiateCoin(Vector2 EnemyPosition)
{
	Texture = LoadTexture("Currency.png");
	Rect = { EnemyPosition.x, EnemyPosition.y, (float)Texture.width, (float)Texture.height };
	IsActive = false;
	AnimationTimer = 0;
	SpritePerFrame = 0.1f;
	Frame = 1;
	TotalFrames = 3;
	Speed = 1;
}
void CURRENCY::MoveCoin(PLAYER Player)
{
	Vector2 Direction = { Rect.x - Player.GetPosition().x, Rect.y - Player.GetPosition().y };
	Rect.x -= Direction.x * GetFrameTime() * Speed;
	Rect.y -= Direction.y * GetFrameTime() * Speed;
}
void CURRENCY::DrawCoin()
{
	Animation({ Rect.x, Rect.y }, &Frame, TotalFrames, Texture, &AnimationTimer, SpritePerFrame, WHITE);
}

//Stars
void STAR::StarHandler(PLAYER * Player)
{
	MoveStar();
	DrawStar(Player);
}
void STAR::DrawStar(PLAYER * Player)
{
	if (IsActive)
	{
		//Radius = (float)RandomNumber(11, 15) / 10;
		if (!ShootingStar)
			DrawCircle(Position.x, Position.y, Radius, YELLOW);
		else if (ShootingStar)
		{
			DrawTexture(ShootingStarTexture, Position.x, Position.y, WHITE);
			if(Wished)
				DrawText("PRESS SPACE TO WISH", (GetScreenWidth() / 10) * 2, (GetScreenHeight() / 6) * 5, 48, WHITE);
			if (IsKeyPressed(KEY_SPACE) && Wished)
			{
				if ((*Player).Health < (*Player).MaxHealth)
				{
					(*Player).Health += 1;
					Wished = false;
				}
			}
		}
	}
}
void STAR::MoveStar()
{
	if(!ShootingStar)
		Position.x -= GetFrameTime() * (Radius * 100);
	else if (ShootingStar)
	{
		Position.x -= GetFrameTime() * (Radius * 100) * 2;
		Position.y += GetFrameTime() * (Radius * 50);
	}

	if (Position.x < 0)
	{
		IsActive = false;
	}
}
void STAR::InstantiateStar(STAR * Star, int SizeOfStars,int MinX, int MaxX)
{
	if (MaxX == 0)MaxX = 1;

	Position = { /*((float)RandomNumber(MinX, MaxX)),
	(float)RandomNumber(0, GetScreenHeight())*/(float)RandomNumber(800, 1250), (float)RandomNumber(0, 450) };
	Radius = RandomNumber(1, 20) / 8;
	ShootingStar = false;
	IsActive = false;
}
void STAR::InstantiateShootingStar(STAR * Star, int SizeOfStars, int MinX, int MaxX)
{
	if (MaxX == 0)MaxX = 1;

	Position = { ((float)RandomNumber(MinX, MaxX)),
		0 };
	Radius = 2;
	ShootingStarTexture = LoadTexture("ShootingStar.png");
	ShootingStar = true;
	IsActive = false;
	Wished = true;
}

void SpawnCoin(Vector2 Position, CURRENCY * Currency, int CurrencySize)
{
	for (int i = 0; i < CurrencySize; i++)
	{
		if (!Currency[i].IsActive)
		{
			Currency[i].InstantiateCoin(Position);
			Currency[i].IsActive = true;
			break;
		}
	}
}

void PlayerBulletOrginizer(PLAYER Player, BULLET * bullet, int SizeOfBullets)
{

	if (IsKeyPressed(Player.Controls.MainShoot) || IsMouseButtonPressed(Player.Controls.MainShoot))
	{
		for (int i = 0; i < SizeOfBullets; i++)
		{
			if (!bullet[i].IsActive)
			{
				bullet[i].InitilizeBullet(Player, 1, {}, 250);
				bullet[i].IsActive = true;
				bullet[i].Target = 1;
				break;
			}
		}
	}
}
void EnemyBulletOrginizer(ENEMY * Enemies, int SizeOfEnemies, BULLET * bullet, int SizeOfBullets)
{
	for (int j = 0; j < SizeOfEnemies; j++)
	{
		if (Enemies[j].IsAlive && Enemies[j].ShootTimer > 2)
		{
			for (int i = 0; i < SizeOfBullets; i++)
			{
				if (!bullet[i].IsActive)
				{
					bullet[i].InitilizeBullet({}, 0, Enemies[j], RandomNumber(200, 300));
					bullet[i].IsActive = true;
					bullet[i].Target == 0;
					Enemies[j].ShootTimer = 0;
					break;
				}
			}
		}
	}
}
void EnemyArrayOrginizer(ENEMY * enemies, int SizeOfEnemies, int *CurrentNumberOfEnemies, int MaxEnemies)
{
	for (int i = *CurrentNumberOfEnemies; i < MaxEnemies; i++)
	{
		for (int j = 0; j < SizeOfEnemies; j++)
		{
			if (!enemies[j].IsAlive)
			{
				enemies[j].InitilizeEnemy(enemies->Basic_Enemy);
				*CurrentNumberOfEnemies += 1;
				enemies[j].IsAlive = true;
				break;
			}
		}
	}
}
void CollectCoin(PLAYER * Player, CURRENCY * Currency, int SizeOfCurrency)
{
	for (int i = 0; i < SizeOfCurrency; i++)
	{
		if (Currency[i].IsActive)
			if (CheckCollisionRecs({ (*Player).GetPosition().x,(*Player).GetPosition().y,
				((*Player).GetTexture().x / 3), (*Player).GetTexture().y }, Currency[i].Rect))
			{
				Currency[i].IsActive = false;
				(*Player).AddCoins(1);
			}
	}
}
void BulletDeletion(BULLET * Bullets, int SizeOfBullet)
{
	for (int i = 0; i < SizeOfBullet; i++)
	{
		if (Bullets[i].Rect.x < 0 || Bullets[i].Rect.x > GetScreenWidth())
		{
			Bullets[i].IsActive = false;
		}
	}
}
void CheckForPlayerDeath(PLAYER * Player, ENEMY * Enemies, int SizeOfEnemies,
	BULLET * Bullets, int SizeOfBullets, int * CurrentEnemies)
{
	if ((*Player).GetHealth() <= 0)
	{
		for (int i = 0; i < SizeOfBullets; i++)
		{
			Bullets[i].IsActive = false;
		}
		for (int i = 0; i < SizeOfEnemies; i++)
		{
			Enemies[i].IsAlive = false;
		}
		(*Player).InitilizePlayer();
		(*CurrentEnemies) = 0;
	}
	
}

int RandomNumber(int Min, int Max)
{
	return(rand() % (Max - Min) + Min);
}

void Animation(Vector2 Pos, int *Frame, int totalFrames,
	Texture2D texture, float * Timer, float TimePerFrame, Color color)
{
	if (*Timer >= TimePerFrame)
	{
		if (*Frame > totalFrames)
			*Frame = 1;
		(*Frame)++;
		*Timer = 0;
	}
	Rectangle Source = { ((texture.width / totalFrames)* (*Frame)), 0,
		(texture.width / totalFrames) , texture.height };
	DrawTextureRec(texture, Source, { Pos.x, Pos.y }, color);
	(*Timer) += GetFrameTime();
}