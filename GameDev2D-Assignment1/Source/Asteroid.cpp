#include "Asteroid.h"
#include "Constants.h"


namespace GameDev2D
{
	Asteroid::Asteroid() :
		m_Velocity(Vector2::Zero),
		m_Position(Vector2::Zero),
		m_AngularVelocity(0.0f),
		m_Angle(0.0f),
		m_MaxRadius(0.0f),
		m_IsActive(true),
		m_Shape{}
	{
		// Create the asteroid shape.
		{
			int numSides = Math::RandomInt( ASTEROID_MIN_SIDES, ASTEROID_MAX_SIDES );

			float radiansPerSide = 2.0f * (float)M_PI / (float)numSides;

			for( int i = 0; i<numSides; i++ )
			{
				float radius = Math::RandomFloat(ASTEROID_MIN_RADIUS, ASTEROID_MAX_RADIUS);
				float angle = i * radiansPerSide;

				if (radius > m_MaxRadius)
					m_MaxRadius = radius;

				m_Shape.push_back( Vector2( cos(angle), sin(angle) ) * radius );
			}

			m_Shape.push_back( m_Shape[0] );
		}

		// Initialize Position, along one of the 4 edges.
		// More or less 2 edges due to wrapping.
		if( Math::RandomInt( 0, 1 ) == 0 )
		{
			// Along top or bottom.
			m_Position.x = Math::RandomFloat( 0, (float)GameDev2D::GetScreenWidth() );
			m_Position.y = (float)Math::RandomInt( 0, 1 ) * GameDev2D::GetScreenHeight();
		}
		else
		{
			// Along left or right.
			m_Position.x = (float)Math::RandomInt( 0, 1 ) * GameDev2D::GetScreenWidth();
			m_Position.y = Math::RandomFloat( 0, (float)GameDev2D::GetScreenHeight() );
		}

		// Initialize velocity and angular velocity.
		float radians = Math::RandomFloat( 0, (float)M_PI*2 );
		float speed = Math::RandomFloat(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
		Vector2 direction = Vector2( cos(radians), sin(radians) );
		m_Velocity = direction * speed;
		m_AngularVelocity = Math::RandomFloat(ASTEROID_MIN_ANGULAR_VELOCITY, ASTEROID_MAX_ANGULAR_VELOCITY );
	}

	void Asteroid::OnUpdate(float delta)
	{
		// Turn.
		m_Angle += m_AngularVelocity * delta;

		// Move.
		m_Position += m_Velocity * delta;

		// Teleport.
		if (m_Position.x < -m_MaxRadius)
		{
			m_Position.x += GameDev2D::GetScreenWidth() + m_MaxRadius * 2.0f;
		}

		if (m_Position.x >= GameDev2D::GetScreenWidth() + m_MaxRadius)
		{
			m_Position.x -= GameDev2D::GetScreenWidth() + m_MaxRadius * 2.0f;
		}

		if (m_Position.y < m_MaxRadius)
		{
			m_Position.y += GameDev2D::GetScreenHeight() + m_MaxRadius * 2.0f;
		}
	
		if (m_Position.y >= GameDev2D::GetScreenHeight() + m_MaxRadius)
		{
			m_Position.y -= GameDev2D::GetScreenHeight() + m_MaxRadius * 2.0f;
		}
	}

	void Asteroid::OnRender(BatchRenderer& batchRenderer)
	{
		if (m_IsActive) {
			batchRenderer.RenderLineStrip(m_Shape, ASTEROID_COLOR, 2, m_Position, m_Angle);

		}
	}
	float Asteroid::GetMaxRadius() const
	{
		return m_MaxRadius;
	}
	Vector2 Asteroid::GetPosition() const
	{
		return m_Position;
	}
	bool Asteroid::IsActive() const
	{
		return m_IsActive;
	}
	void Asteroid::SetIsActiveFalse()
	{
		m_IsActive = false;
	}
}