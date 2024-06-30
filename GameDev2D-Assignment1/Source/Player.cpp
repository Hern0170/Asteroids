#include "Player.h"
#include "Constants.h"

#include "Game.h"

namespace GameDev2D
{
	Player::Player(Game* game) :
		m_Game(game),
		m_CollisionCooldown(2.0f), 
		m_TimeSinceLastHit(2.0f), 
		m_PlayerHealth(PLAYER_HEALTH),
		m_Velocity(Vector2::Zero),
		m_Position(Vector2(GetScreenWidth()* PLAYER_SPAWN_POSITION_X_PCT, GetScreenHeight()* PLAYER_SPAWN_POSITION_Y_PCT)),
		m_Angle(0.0f),
		m_Radius(13.0f),
		m_Controls(Vector2::Zero),
		m_Shape{},
		m_Flame{},
		m_FireLeft(true),
		m_ShieldActive(false),
		m_OrbitRadius(20.0f),
		m_AngularVelocity(300.0f),
		m_Burst(false),
		m_TimerShoot(0.0f),
		m_Charged(false),
		m_BurstFireCount(0)
	{
		// Define the player shape.

		m_Shape.push_back(Vector2(10, 0));
		// Define cannon L
		m_Shape.push_back(Vector2(-6, 8));
		m_Shape.push_back(Vector2(6, 8));
		m_Shape.push_back(Vector2(6, 6));
		m_Shape.push_back(Vector2(-2, 6));


		m_Shape.push_back(Vector2(-10, 10));
		m_Shape.push_back(Vector2(-5, 0));
		m_Shape.push_back(Vector2(-10, -10));
		//Define cannon R
		m_Shape.push_back(Vector2(-2, -6));
		m_Shape.push_back(Vector2(6, -6));
		m_Shape.push_back(Vector2(6, -8));
		m_Shape.push_back(Vector2(-6, -8));
		m_Shape.push_back(Vector2(10, 0));

		//Define flame
		m_Flame.push_back(Vector2(-8, 6));
		m_Flame.push_back(Vector2(-16, 4));
		m_Flame.push_back(Vector2(-10, 2));
		m_Flame.push_back(Vector2(-16, 0));
		m_Flame.push_back(Vector2(-10, -2));
		m_Flame.push_back(Vector2(-16, -4));
		m_Flame.push_back(Vector2(-8, -6));

		
		for (int i = 0; i < 3; i++) {
			m_Radians[i] = i * 2 * M_PI / 3;
		}
	}


	void Player::OnUpdate(float delta)
	{
		if (m_TimeSinceLastHit < m_CollisionCooldown) {
			m_TimeSinceLastHit += delta;  
		}
		if (m_PlayerHealth > 1)
		{
			for (int i = 0; i < 3; i++) {
				m_Radians[i] += Math::DegreesToRadians(m_AngularVelocity) * delta;
				if (m_Radians[i] >= 2 * M_PI) {
					m_Radians[i] -= 2 * M_PI;
				}
			}

		}

		if (m_Burst)
		{
					
					m_BurstFireCount++;
					Shoot();
					if (m_BurstFireCount >= BURST_FIRE_MAX) {
						m_Burst = false;
						m_BurstFireCount = 0;
					}
					
		}

		if (m_Charged) 
		{
			m_TimerShoot += delta;
			//if (m_TimerShoot >= RAPID_FIRE_INTERVAL)
			//{
					Shoot();
					m_TimerShoot = 0.0f;
				
			//}
		}
		

		// Turn.
		m_Angle += -m_Controls.x * PLAYER_TURN_SPEED * delta;

		// Move.
		float acceleration = m_Controls.y * PLAYER_ACCELERATION_RATE;
		float angleRadians = Math::DegreesToRadians(m_Angle);
		Vector2 direction = Vector2(cos(angleRadians), sin(angleRadians));
		m_Velocity += direction * acceleration * delta;
		m_Position += m_Velocity * delta;

		// Cap velocity.
		if (m_Velocity.Length() > PLAYER_MAX_SPEED)
		{
			m_Velocity = m_Velocity.Normalized() * PLAYER_MAX_SPEED;
		}

		// Teleport.
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


		if (m_Controls.y == 1)
		{
			m_FlameTimer += delta;
			if (m_FlameTimer >= 0.1f)
			{
				m_FlameColorToggle = !m_FlameColorToggle;
				m_FlameTimer = 0.0f;
			}
		}
		else
		{
			m_FlameTimer = 0.0f;
		}



	}

	void Player::OnRender(BatchRenderer& batchRenderer)
	{
		if (m_PlayerHealth > 1) 
		{
			for (int i = 0; i < 3; i++) 
			{
				float x = m_Position.x + cos(m_Radians[i]) * m_OrbitRadius;
				float y = m_Position.y + sin(m_Radians[i]) * m_OrbitRadius;
				batchRenderer.RenderCircle(x, y, 2.0f, NULL, GameDev2D::ColorList::Green, 2.0f);  // Renderiza cada círculo
			}
			
		}
		if (m_Controls.y == 1)
		{
			GameDev2D::Color flameColor = m_FlameColorToggle ? GameDev2D::ColorList::OrangeRed : GameDev2D::ColorList::Orange;
			batchRenderer.RenderLineStrip(m_Flame, flameColor, 2, m_Position, m_Angle);
		}
		batchRenderer.RenderLineStrip(m_Shape, PLAYER_COLOR, 2, m_Position, m_Angle);
		
	}

	void Player::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{
		if (keyState == KeyState::Down)
		{
			if (keyCode == KeyCode::Space)
			{
				if(!m_Burst) Shoot();	

			}
			if (keyCode == KeyCode::R)
			{
					m_Burst = true;
				
			}

			if (keyCode == KeyCode::Q)
			{
				m_Charged = true;
			}
			if (keyCode == KeyCode::Up || keyCode == KeyCode::W)
			{
				m_Controls.y = 1;
			}
			else if (keyCode == KeyCode::Left || keyCode == KeyCode::A)
			{
				m_Controls.x = -1;
			}
			else if (keyCode == KeyCode::Right || keyCode == KeyCode::D)
			{
				m_Controls.x = 1;
			}

		}
		

		if (keyState == KeyState::Up)
		{
			if (keyCode == KeyCode::Q)
			{
				m_Charged = false;
			}
			if (keyCode == KeyCode::Up || keyCode == KeyCode::W)
			{
				m_Controls.y = 0;
			}
			else if (keyCode == KeyCode::Left || keyCode == KeyCode::A)
			{
				
				m_Controls.x = 0;
			}
			else if (keyCode == KeyCode::Right || keyCode == KeyCode::D)
			{
				m_Controls.x = 0;
			}
		}
	}
	void Player::Shoot()
	{
		m_FireLeft = !m_FireLeft;

		float angleRadians = Math::DegreesToRadians(m_Angle);
		float angleOffset = 0.01f;
		float magnitude = 8.0f;
		float radians = 0.0f;

		Vector2 direction;
		Vector2 position;

		if (m_FireLeft)
		{
			direction = Vector2(cos(angleRadians - angleOffset), sin(angleRadians - angleOffset));

			radians = static_cast<float>(angleRadians + M_PI_2); // Half pi or 90 degrees
			Vector2 leftEdge = Vector2(cos(radians) , sin(radians)) * magnitude;
			position = m_Position + leftEdge;
		}
		else
		{
			direction = Vector2(cos(angleRadians + angleOffset), sin(angleRadians + angleOffset));

			radians = static_cast<float>(angleRadians - M_PI_2); // Half pi or 90 degrees
			Vector2 rightEdge = Vector2(cos(radians), sin(radians)) * magnitude;
			position = m_Position + rightEdge;
		}

		Vector2 velocity = direction * LASER_SPEED; 
		if (m_Burst) 
		{
			m_Game->SpawnBullet(position, velocity, BULLET_BURST_COLOR, BULLET_BURST_RADIUS_INC);
		}
		else if(m_Charged)
		{
			m_Game->SpawnBullet(position, velocity , BULLET_CHARGED_COLOR, BULLET_CHARGED_RADIUS_INC);

		}
		else
		{
			m_Game->SpawnBullet(position, velocity, GameDev2D::Color::Random(), BULLET_RADIUS_INC);
		}

	}
	float Player::GetRadius() const
	{
		return m_Radius;
	}
	Vector2 Player::GetPosition() const
	{
		return m_Position;
	}
	int Player::GetHealth() const
	{
		return m_PlayerHealth;
	}
	void Player::SetHealth(int h)
	{
		m_PlayerHealth = h;
	}
	void Player::ResetCollisionTimer()
	{
		m_TimeSinceLastHit = 0;
	}
	bool Player::CanBeHit()
	{
		return m_TimeSinceLastHit >= m_CollisionCooldown;
	}
	void Player::ActivateShield()
	{
	}
	void Player::DeactivateShield()
	{
	}
	void Player::SetPosition()
	{
		m_Position = Vector2(Math::RandomFloat(0, (float)GameDev2D::GetScreenWidth()), Math::RandomFloat(0, (float)GameDev2D::GetScreenHeight()));
	}
}