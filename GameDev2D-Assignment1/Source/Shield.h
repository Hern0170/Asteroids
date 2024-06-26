#pragma once
class Shield
{
};

#include <GameDev2D.h>

namespace GameDev2D
{
	class Shield
	{
	public:
		Shield(const Vector2& position);
		Shield();

		void OnUpdate(float delta);
		void OnRender(BatchRenderer& batchRenderer);

		float GetRadius() const;
		Vector2 GetPosition() const;


		bool IsActive() const;
		void SetIsActiveFalse();
		void SetIsActiveTrue();

		void Activate(const Vector2& position);


	private:
		Vector2 m_Position;   
		std::vector<Vector2> m_Shape;
		float m_Angle;
		bool m_IsActive;

		float m_Radius;
		float m_ShieldTimer;

	};
	

	
}