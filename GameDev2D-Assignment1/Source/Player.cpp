#include "Player.h"
#include "Constants.h"
#include "Game.h"

namespace GameDev2D
{
	Player::Player(Game* game) :
		m_Game(game),
		m_Velocity(Vector2::Zero),
		m_Position(Vector2(GetScreenWidth()* PLAYER_SPAWN_POSITION_X_PCT, GetScreenHeight()* PLAYER_SPAWN_POSITION_Y_PCT)),
		m_Angle(0.0f),
		m_Controls(Vector2::Zero),
		m_Shape{},
		m_Flame{},
		m_FireLeft(true)
	{
		// Define the player shape.

		m_Shape.push_back( Vector2(  10,   0 ) );
		// Define cannon L
		m_Shape.push_back(Vector2(-6, 8));
		m_Shape.push_back(Vector2(6, 8));
		m_Shape.push_back(Vector2(6, 6));
		m_Shape.push_back(Vector2(-2, 6));


		m_Shape.push_back( Vector2( -10,  10 ) );
		m_Shape.push_back( Vector2(  -5,   0 ) );
		m_Shape.push_back( Vector2( -10, -10 ) );
		//Define cannon R
		m_Shape.push_back(Vector2(-2, -6));
		m_Shape.push_back(Vector2(6, -6));
		m_Shape.push_back(Vector2(6, -8));
		m_Shape.push_back(Vector2(-6, -8));
		m_Shape.push_back( Vector2(  10,   0 ) );

		//Define flame
		m_Flame.push_back(Vector2(-8,6));
		m_Flame.push_back(Vector2(-16, 4));
		m_Flame.push_back(Vector2(-10, 2));
		m_Flame.push_back(Vector2(-16, 0));
		m_Flame.push_back(Vector2(-10, -2));
		m_Flame.push_back(Vector2(-16, -4));
		m_Flame.push_back(Vector2(-8, -6));


		m_Bullets.reserve(BULLET_POOL_SIZE);
		for (int i = 0; i < BULLET_POOL_SIZE; ++i) {
			m_Bullets.push_back(new Bullet());
		}
	}

	//Player::~Player()
	//{
	//	for (auto* bullet : m_Bullets) {
	//		delete bullet;
	//	}
	//}

	void Player::OnUpdate(float delta)
	{


		// Turn.
		m_Angle += -m_Controls.x * PLAYER_TURN_SPEED * delta;
		
		// Move.
		float acceleration = m_Controls.y * PLAYER_ACCELERATION_RATE;
		float angleRadians = Math::DegreesToRadians( m_Angle );
		Vector2 direction = Vector2( cos(angleRadians), sin(angleRadians) );
		m_Velocity += direction * acceleration * delta;
		m_Position += m_Velocity * delta;

		// Cap velocity.
		if( m_Velocity.Length() > PLAYER_MAX_SPEED)
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

		//for (auto* bullet : m_Bullets) {
		//	if (bullet->IsActive()) {
		//		bullet->OnUpdate(delta);
		//	}
		//}
	
	}

	void Player::OnRender(BatchRenderer& batchRenderer)
	{
		if (m_Controls.y == 1)
		{
			GameDev2D::Color flameColor = m_FlameColorToggle ? GameDev2D::ColorList::OrangeRed : GameDev2D::ColorList::Orange;
			batchRenderer.RenderLineStrip(m_Flame, flameColor, 2, m_Position, m_Angle);
		}
		batchRenderer.RenderLineStrip( m_Shape, PLAYER_COLOR, 2, m_Position, m_Angle );



		/*for (Bullet* bullet : m_Bullets) {
			if (bullet->IsActive()) {
				bullet->OnRender(batchRenderer);
			}
		}*/
	}

	void Player::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{
		if( keyState == KeyState::Down )
		{
			if (keyCode == KeyCode::Space)
			{
				Shoot();

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

		if( keyState == KeyState::Up )
		{
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

			radians = angleRadians + M_PI_2; // Half pi or 90 degrees
			Vector2 leftEdge = Vector2(cos(radians), sin(radians)) * magnitude;
			position = m_Position + leftEdge;
		}
		else
		{
			direction = Vector2(cos(angleRadians + angleOffset), sin(angleRadians + angleOffset));

			radians = angleRadians - M_PI_2; // Half pi or 90 degrees
			Vector2 rightEdge = Vector2(cos(radians), sin(radians)) * magnitude;
			position = m_Position + rightEdge;
		}

		Vector2 velocity = direction * 500.0f; // Velocidad de la bala

		m_Game->SpawnBullet(position, velocity);
	}

	//Bullet* Player::GetBulletFromPool()
	//{
	//	for (auto* bullet : m_Bullets) {
	//		if (!bullet->IsActive()) {
	//			return bullet;
	//		}
	//	}
	//	return nullptr;
	//}
}