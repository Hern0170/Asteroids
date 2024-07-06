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
		float GetRadius() const;
		Vector2 GetPosition() const;
		int GetHealth() const;
		void SetHealth(int h);

		void ResetCollisionTimer(); 
		bool CanBeHit();


		void ActivateShield();
		void DeactivateShield();

		void SetPosition();

		bool GetCharged();

	private:

		Game* m_Game;

		//Movement
		Vector2 m_Velocity;
		Vector2 m_Position;
		float m_Angle;
		Vector2 m_Controls;
		float m_Radius;

		//Ship Shape
		std::vector<Vector2> m_Shape;
		std::vector<Vector2> m_Flame;

		//Flame Properties
		float m_FlameTimer; 
		bool m_FlameColorToggle;
		bool m_FireLeft;



		//Collision properties
		float m_CollisionCooldown; 
		float m_TimeSinceLastHit;

		// Shield properties
		int m_PlayerHealth;

		bool m_ShieldActive;
		float m_OrbitRadius;
		float m_Radians[3];  
		float m_AngularVelocity;  

		bool m_Burst;
		float m_TimerShoot;

		bool m_Charged;
		float m_TimerChargedShoot;
		int m_BurstFireCount;

		Audio m_SoundBasicShoot;
		Audio m_SoundBurstShoot;
		Audio m_SoundChargedtShoot;
		Audio m_SoundPlayerMove;


	};
}
