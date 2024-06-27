#pragma once

#include <GameDev2D.h>
#include <vector>

#include "Player.h"
#include "Asteroid.h"
#include "Constants.h"
#include "Shield.h"

namespace GameDev2D
{
	class Game

	{
	public:
		Game();
		~Game();

		//Write game logic in the Update method
		void OnUpdate(float delta);

		//Render game objects in the Draw method
		void OnRender(BatchRenderer& batchRenderer);

		//Input event methods
		void OnKeyEvent(KeyCode keyCode, KeyState keyState);
		void OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY);
		void OnMouseMovedEvent(float mouseX, float mouseY);

		void SpawnBullet(const Vector2& position, const Vector2& velocity);
		void SpawnShield(const Vector2& position);


		bool CheckCollision(const Player* player, const Asteroid* asteroid);
		bool CheckCollision(const Bullet* bullet, const Asteroid* asteroid);
		bool CheckCollision(const Shield* shield, const Player* Player);
		bool CheckCollision(const Shield* shield, const Asteroid* asteroid);

		void Player_AsteroidCollision(Player* player, Asteroid& asteroid);
		void Player_ShieldCollision(Player* player,Shield* shield);

		void Bullet_AsteroidCollision(Bullet* Bullet , Asteroid& asteroid);


		//void Shield_AsteroidCollision(Bullet bullet, Asteroid& asteroid);

		void End();


	private:
		Bullet* GetBulletFromPool();
		Shield* GetShieldFromPool();

		Player* m_Player;
		std::vector<Asteroid> m_Asteroids;
		//std::vector<Shield> m_Shield;
		Shield* m_Shield[SHIELD_POOL_SIZE];
		Bullet* m_Bullet[BULLET_POOL_SIZE];

		SpriteFont m_TextHealth;
		SpriteFont m_TextAsteroids;
		SpriteFont m_TextWin;
		SpriteFont m_TextTime;


		float m_Timer;
		int m_asteroidsCount;
		bool m_Playing;

	};
}
