#pragma once

#include <GameDev2D.h>
#include "Bullet.h"
//#include "Game.h"

namespace GameDev2D
{

	class Game;

	class Player
	{
	public:
		Player(Game* game);
		//~Player();

		void OnUpdate(float delta);
		void OnRender(BatchRenderer& batchRenderer);
		void OnKeyEvent(KeyCode keyCode, KeyState keyState);
		void Shoot();


	private:
		Game* m_Game;
		Vector2 m_Velocity;
		Vector2 m_Position;
		float m_Angle;
		Vector2 m_Controls;

		std::vector<Vector2> m_Shape;
		std::vector<Vector2> m_Flame;
		std::vector<Bullet*> m_Bullets;
		Bullet* GetBulletFromPool();


		float m_FlameTimer; // Temporizador para cambiar el color de la flama
		bool m_FlameColorToggle; // Estado del color de la flama
		bool m_FireLeft;
	};
}
