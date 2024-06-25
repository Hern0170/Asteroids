#pragma once

#include <GameDev2D.h>
#include "Bullet.h"

namespace GameDev2D
{
	class Player
	{
	public:
		Player();
		~Player();

		void OnUpdate(float delta);
		void OnRender(BatchRenderer& batchRenderer);
		void OnKeyEvent(KeyCode keyCode, KeyState keyState);
		void Shoot();


	private:
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
