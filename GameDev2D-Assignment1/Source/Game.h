#pragma once

#include <GameDev2D.h>
#include <vector>

#include "Player.h"
#include "Asteroid.h"
#include "Constants.h"

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
		bool CheckCollision(const Player* player, const Asteroid* asteroid);
		bool CheckCollision(const Bullet* bullet, const Asteroid* asteroid);
		void Player_AsteroidCollision(Player* Player, Asteroid& asteroid);
		void Bullet_AsteroidCollision(Bullet* Bullet , Asteroid& asteroid);


	private:
		Bullet* GetBulletFromPool();
		Player* m_Player;
		std::vector<Asteroid> m_Asteroids;
		Bullet* m_Bullet[BULLET_POOL_SIZE];

	};
}
