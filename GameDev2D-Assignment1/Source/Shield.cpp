#include "Shield.h"
#include "Constants.h"

namespace GameDev2D
{
	GameDev2D::Shield::Shield() :
		m_Position(Vector2::Zero),
		m_IsActive(false),
		m_Angle(0.0f),
		m_Radius(1.0f)

	{
		m_Shape.push_back(Vector2(0, 5));
		m_Shape.push_back(Vector2(10, 0));
		m_Shape.push_back(Vector2(0, -5));
		m_Shape.push_back(Vector2(-10, 0));
		m_Shape.push_back(Vector2(0, 5));
	}

	GameDev2D::Shield::Shield(const Vector2& position) :
		m_Position(position),
		m_IsActive(false),
		m_Angle(0.0f)

	{
		m_Shape.push_back(Vector2(0, 5));
		m_Shape.push_back(Vector2(10, 0));
		m_Shape.push_back(Vector2(0, -5));
		m_Shape.push_back(Vector2(-10, 0));
		m_Shape.push_back(Vector2(0, 5));
	}

	void GameDev2D::Shield::OnUpdate(float delta)
	{

		if (m_IsActive) {


			m_ShieldTimer += delta;
			if (m_ShieldTimer >= SHIELD_TIME_ACTIVE) {
				m_IsActive = false;
				m_ShieldTimer = 0.0f;
			}

			if (m_Position.x < 0)
			{
				m_Position.x += GameDev2D::GetScreenWidth();
			}

			if (m_Position.x >= GameDev2D::GetScreenWidth())
			{
				m_Position.x -= GameDev2D::GetScreenWidth();
			}

			if (m_Position.y < 0)
			{
				m_Position.y += GameDev2D::GetScreenHeight();
			}

			if (m_Position.y >= GameDev2D::GetScreenHeight())
			{
				m_Position.y -= GameDev2D::GetScreenHeight();
			}

		}
	}

	void GameDev2D::Shield::OnRender(BatchRenderer& batchRenderer)
	{
		if (m_IsActive) 
		{
			batchRenderer.RenderLineStrip(m_Shape, PLAYER_COLOR, 2, m_Position, m_Angle);

		}
	}


	float Shield::GetRadius() const
	{
		return m_Radius;
	}

	Vector2 GameDev2D::Shield::GetPosition() const
	{
		return m_Position;
	}

	bool GameDev2D::Shield::IsActive() const
	{
		return m_IsActive;
	}

	void GameDev2D::Shield::SetIsActiveFalse()
	{
		m_IsActive = false;
	}

	void Shield::SetIsActiveTrue()
	{
		m_IsActive = true;
	}

	void Shield::Activate(const Vector2& position)
	{
		m_Position = position;
		m_IsActive = true;
		m_ShieldTimer = 0.0f;

	}

}