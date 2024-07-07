#pragma once

#include <GameDev2D.h>

namespace GameDev2D
{
	class Asteroid
	{
	public:
		Asteroid();

		void OnUpdate(float delta);
		void OnRender(BatchRenderer& batchRenderer);

		float GetMaxRadius() const;
		void SetMaxRadius(float radius);
		Vector2 GetPosition() const;

		bool IsActive() const;
		void SetIsActiveFalse();

	private:
		Vector2 m_Velocity;
		Vector2 m_Position;
		float m_AngularVelocity;
		float m_Angle;
		float m_MaxRadius;
		std::vector<Vector2> m_Shape;
		bool m_IsActive;

	};
}
