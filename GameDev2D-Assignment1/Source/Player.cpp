#include "Player.h"
#include "Constants.h"

#include "Game.h"
namespace GameDev2D
{
	Player::Player(Game* game) :
		m_Game(game),
		m_CollisionCooldown(PLAYER_COOLDOWN),
		m_TimeSinceLastHit(PLAYER_COOLDOWN),
		m_PlayerHealth(PLAYER_HEALTH),
		m_Velocity(Vector2::Zero),
		m_Position(Vector2(GetScreenWidth()* PLAYER_SPAWN_POSITION_X_PCT, GetScreenHeight()* PLAYER_SPAWN_POSITION_Y_PCT)),
		m_Angle(0.0f),
		m_Radius(13.0f),
		m_Controls(Vector2::Zero),
		m_FlameColorToggle(false),
		m_FlameTimer(0),
		m_FireLeft(true),
		m_ShieldActive(false),
		m_OrbitRadius(20.0f),
		m_AngularVelocity(300.0f),
		m_Burst(false),
		m_BurstActive(false),
		m_TimerShoot(0.0f),
		m_Charged(false),
		m_BurstFireCount(0),
		m_SoundBasicShoot("BaseShoot"),
		m_SoundBurstShoot("BurstShoot"),
		m_SoundChargedShoot("ChargedShoot_A"),
		m_SoundPlayerMove("PlayerMove_A")
	{
		
		InitializeGraphics();
		InitializeSounds();
	}

	void Player::InitializeGraphics()
	{
		InitializeShape();
		InitializeFlame();
		InitializeShields();
	}

	void Player::InitializeShape()
	{
		m_Shape.push_back(Vector2(10, 0));
		m_Shape.push_back(Vector2(-6, 8));
		m_Shape.push_back(Vector2(6, 8));
		m_Shape.push_back(Vector2(6, 6));
		m_Shape.push_back(Vector2(-2, 6));
		m_Shape.push_back(Vector2(-10, 10));
		m_Shape.push_back(Vector2(-5, 0));
		m_Shape.push_back(Vector2(-10, -10));
		m_Shape.push_back(Vector2(-2, -6));
		m_Shape.push_back(Vector2(6, -6));
		m_Shape.push_back(Vector2(6, -8));
		m_Shape.push_back(Vector2(-6, -8));
		m_Shape.push_back(Vector2(10, 0));
	}

	void Player::InitializeFlame()
	{
		m_Flame.push_back(Vector2(-8, 6));
		m_Flame.push_back(Vector2(-16, 4));
		m_Flame.push_back(Vector2(-10, 2));
		m_Flame.push_back(Vector2(-16, 0));
		m_Flame.push_back(Vector2(-10, -2));
		m_Flame.push_back(Vector2(-16, -4));
		m_Flame.push_back(Vector2(-8, -6));
	}



	void Player::InitializeSounds()
	{
		m_SoundPlayerMove.SetDoesLoop(true);
		m_SoundPlayerMove.SetVolume(SOUND_VOLUME);
		m_SoundBasicShoot.SetVolume(SOUND_VOLUME);
		m_SoundBurstShoot.SetVolume(SOUND_VOLUME);
		m_SoundChargedShoot.SetVolume(SOUND_VOLUME);
	}

	void Player::InitializeShields()
	{
		for (int i = 0; i < 3; i++) {
			m_Radians[i] = i * 2 * static_cast<float>(M_PI) / 3;
		}
	}

	void Player::OnUpdate(float delta)
	{
		UpdateCollisionCooldown(delta);
		UpdateShieldOrbit(delta);
		ProcessShootingMechanics(delta);
		UpdateMovementAndScreenWrapping(delta);
		FlameInterval(delta);
		
	}
	void Player::FlameInterval(float delta)
	{
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
	void Player::UpdateCollisionCooldown(float delta)
	{
		if (m_TimeSinceLastHit < m_CollisionCooldown) {
			m_TimeSinceLastHit += delta;
		}
	}

	void Player::UpdateShieldOrbit(float delta)
	{
		if (m_PlayerHealth > PLAYER_HEALTH) {
			for (int i = 0; i < 3; i++) {
				m_Radians[i] += Math::DegreesToRadians(m_AngularVelocity) * delta;
				if (m_Radians[i] >= 2 * static_cast<float>(M_PI)) {
					m_Radians[i] -= 2 * static_cast<float>(M_PI);
				}
			}
		}
	}

	void Player::ProcessShootingMechanics(float delta)
	{
		HandleBurstShooting(delta);
		HandleChargedShooting(delta);
	}

	void Player::HandleBurstShooting(float delta)
	{
		if (m_Burst) {
			if (m_Game->GetIsShooting()) {
				m_SoundBurstShoot.Play();
			}
			m_BurstFireCount++;
			Shoot();
			if (m_BurstFireCount >= BURST_FIRE_MAX) {
				m_Burst = false;
				m_BurstFireCount = 0;
				m_SoundBurstShoot.Stop();
				m_BurstActive = true;
			}
		}
	}

	void Player::HandleChargedShooting(float delta)
	{
		if (m_Charged && m_TimerChargedShoot <= CHARGED_FIRE_MAX)
		{
			m_TimerChargedShoot ++;
			if (m_TimerChargedShoot <= CHARGED_FIRE_MAX)
			{
				if (m_Game->GetIsShooting())
				{
					m_SoundChargedShoot.Play();
				}
				Shoot();
			}
		}
		else 
		{
			m_Charged = false;
		}
	}

	void Player::UpdateMovementAndScreenWrapping(float delta)
	{
		m_Angle += -m_Controls.x * PLAYER_TURN_SPEED * delta;
		float acceleration = m_Controls.y * PLAYER_ACCELERATION_RATE;
		float angleRadians = Math::DegreesToRadians(m_Angle);
		Vector2 direction = Vector2(cos(angleRadians), sin(angleRadians));
		m_Velocity += direction * acceleration * delta;
		m_Position += m_Velocity * delta;

		if (m_Velocity.Length() > PLAYER_MAX_SPEED) {
			m_Velocity = m_Velocity.Normalized() * (m_Charged ? CHARGED_MAX_SPEED : PLAYER_MAX_SPEED);
		}

		WrapPosition();
	}

	void Player::WrapPosition()
	{
		if (m_Position.x < 0) {
			m_Position.x += GameDev2D::GetScreenWidth();
		}
		if (m_Position.x >= GameDev2D::GetScreenWidth()) {
			m_Position.x -= GameDev2D::GetScreenWidth();
		}
		if (m_Position.y < 0) {
			m_Position.y += GameDev2D::GetScreenHeight();
		}
		if (m_Position.y >= GameDev2D::GetScreenHeight()) {
			m_Position.y -= GameDev2D::GetScreenHeight();
		}
	}

	void Player::OnRender(BatchRenderer& batchRenderer)
	{
		RenderShield(batchRenderer);
		RenderFlame(batchRenderer);
		RenderShip(batchRenderer);
		if (m_Charged) {
			batchRenderer.RenderCircle(m_Position.x, m_Position.y, 14.0f, NULL, GameDev2D::ColorList::LightBlue, 3.0f);
		}
	}

	void Player::RenderShield(BatchRenderer& batchRenderer)
	{
		if (m_PlayerHealth > 1) {
			for (int i = 0; i < 3; i++) {
				float x = m_Position.x + cos(m_Radians[i]) * m_OrbitRadius;
				float y = m_Position.y + sin(m_Radians[i]) * m_OrbitRadius;
				batchRenderer.RenderCircle(x, y, 2.0f, NULL, GameDev2D::ColorList::Green, 2.0f);
			}
		}
	}

	void Player::RenderFlame(BatchRenderer& batchRenderer)
	{
		if (m_Controls.y == 1) {
			GameDev2D::Color flameColor = m_FlameColorToggle ? GameDev2D::ColorList::Red : GameDev2D::ColorList::Orange;
			batchRenderer.RenderLineStrip(m_Flame, flameColor, 2, m_Position, m_Angle);
		}
	}

	void Player::RenderShip(BatchRenderer& batchRenderer)
	{
		batchRenderer.RenderLineStrip(m_Shape, PLAYER_COLOR, 2, m_Position, m_Angle);
	}

	void Player::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{
		if (m_Game->GetPlaying()) 
		{
			if (keyState == KeyState::Down) 
			{
				if (keyCode == KeyCode::Space) 
				{
					if (!m_Burst) 
					{
						m_SoundBasicShoot.Play();
						Shoot();
					}
				}
				if (keyCode == KeyCode::E) 
				{
					m_Burst = true;
				}
				if (keyCode == KeyCode::Q) 
				{
					if (m_TimerChargedShoot <= CHARGED_FIRE_MAX)
					{
						m_Charged = true;
						m_TimerChargedShoot++;
					}
					else 
					{
						m_Charged = false;

					}
				}
				if (keyCode == KeyCode::Up || keyCode == KeyCode::W) 
				{
					m_SoundPlayerMove.Play();
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
					m_TimerChargedShoot = 0.0f;
					m_SoundChargedShoot.Stop();
				}
				if (keyCode == KeyCode::Up || keyCode == KeyCode::W) 
				{
					m_SoundPlayerMove.Stop();
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
		Vector2 velocity;

		if (m_FireLeft) 
		{
			direction = Vector2(cos(angleRadians - angleOffset), sin(angleRadians - angleOffset));
			radians = static_cast<float>(angleRadians + M_PI_2);
			Vector2 leftEdge = Vector2(cos(radians), sin(radians)) * magnitude;
			position = m_Position + leftEdge;
		}
		else 
		{
			direction = Vector2(cos(angleRadians + angleOffset), sin(angleRadians + angleOffset));
			radians = static_cast<float>(angleRadians - M_PI_2);
			Vector2 rightEdge = Vector2(cos(radians), sin(radians)) * magnitude;
			position = m_Position + rightEdge;
		}

		if (!m_Charged) 
		{
			velocity = direction * LASER_SPEED;
		}
		else {
			velocity = direction * -CHARGED_FIRE_DELAY;
		}

		if (m_Burst) 
		{
			m_Game->SpawnBullet(position, velocity, BULLET_BURST_COLOR, BULLET_BURST_RADIUS_INC);
		}
		else if (m_Charged) 
		{
			m_Game->SpawnBullet(position, velocity, GameDev2D::ColorList::LightBlue, BULLET_CHARGED_RADIUS_INC);
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
		m_ShieldActive = true;
	}

	void Player::DeactivateShield()
	{
		m_ShieldActive = false;
	}

	void Player::SetPosition()
	{
		m_Position = Vector2(Math::RandomFloat(0, (float)GameDev2D::GetScreenWidth()), Math::RandomFloat(0, (float)GameDev2D::GetScreenHeight()));
	}

	bool Player::GetCharged()
	{
		return m_Charged;
	}

	void Player::StopSoundPlayer()
	{
		m_SoundBasicShoot.Stop();
		m_SoundBurstShoot.Stop();
		m_SoundChargedShoot.Stop();
		m_SoundPlayerMove.Stop();
	}
}