#include "Game.h"



namespace GameDev2D
{
	Game::Game() :
		m_TextHealth("OpenSans-CondBold_72"),
		m_Player(nullptr),
		m_Asteroids{}
	{
		m_Player = new Player(this);
		for( int i = 0; i < NUM_ASTEROIDS; i++ )
		{
			m_Asteroids.push_back(Asteroid());
		}
		for (int i = 0; i < BULLET_POOL_SIZE; i++)
		{
			m_Bullet[i] = new Bullet();
		}

		m_TextHealth.SetText("Lives: " + std::to_string(m_Player->GetHealth()));

	}

	Game::~Game()
	{
		if (m_Player != nullptr)
		{
			delete m_Player;
			m_Player = nullptr;
		}

		for (int i = 0; i < BULLET_POOL_SIZE; i++)
		{
			if (m_Bullet[i] != nullptr)
			{
				delete m_Bullet[i];
				m_Bullet[i] = nullptr;
			}
		}

	}

	void Game::OnUpdate(float delta)
	{
		m_Player->OnUpdate( delta );
		for (unsigned int i = 0; i < m_Asteroids.size(); i++)
		{
			m_Asteroids.at(i).OnUpdate( delta );
		}

		for (int i = 0; i < BULLET_POOL_SIZE; i++)
		{
			m_Bullet[i]->OnUpdate(delta);
		}

		for (Asteroid& asteroid : m_Asteroids) {
			if (CheckCollision(m_Player, &asteroid)) {
				Player_AsteroidCollision(m_Player, asteroid);
			}
		}


		for (auto& bullet : m_Bullet) {
			if (!bullet->IsActive()) continue;
			for (auto& asteroid : m_Asteroids) {
				if (CheckCollision(bullet, &asteroid)) {
					Bullet_AsteroidCollision(bullet, asteroid);
				}
			}
		}
	}

	void Game::OnRender(BatchRenderer& batchRenderer)
	{
		batchRenderer.BeginScene();
		batchRenderer.RenderSpriteFont(m_TextHealth);
		for (int i = 0; i < BULLET_POOL_SIZE; i++)
		{
			m_Bullet[i]->OnRender(batchRenderer);
		}
		m_Player->OnRender( batchRenderer );
		for (unsigned int i = 0; i < m_Asteroids.size(); i++)
		{
			m_Asteroids.at(i).OnRender( batchRenderer );
		}

		batchRenderer.EndScene();
	}


	void Game::SpawnBullet(const Vector2& position, const Vector2& velocity)
	{
		Bullet* bullet = GetBulletFromPool();
		if (bullet != nullptr)
		{
			bullet->Activate(position, velocity);
		}
	}

	bool Game::CheckCollision(const Player* player, const Asteroid* asteroid)
	{
		Vector2 diff = player->GetPosition() - asteroid->GetPosition();
		float distanceSquared = diff.LengthSquared();
		float radiiSum = player->GetRadius() + asteroid->GetMaxRadius();
		return distanceSquared <= (radiiSum * radiiSum);
	}

	bool Game::CheckCollision(const Bullet* bullet, const Asteroid* asteroid)
	{
		if (!bullet->IsActive() || !asteroid->IsActive()) return false; 

		Vector2 diff = bullet->GetPosition() - asteroid->GetPosition();
		float distanceSquared = diff.LengthSquared();
		float radiiSum = bullet->GetRadius() + asteroid->GetMaxRadius();
		return distanceSquared <= (radiiSum * radiiSum);
	}

	void Game::Player_AsteroidCollision(Player* player, Asteroid& asteroid)
	{
		if (player->CanBeHit() && asteroid.IsActive()) {  
			player->SetHealth(player->GetHealth() - 1); 
			m_TextHealth.SetText("Lives: " + std::to_string(player->GetHealth()));
			player->ResetCollisionTimer();  

			if (player->GetHealth() <= 0) {
				exit(0);  
			}
		}
		
	}

	void Game::Bullet_AsteroidCollision(Bullet* bullet, Asteroid& asteroid)
	{
		asteroid.SetIsActiveFalse();
		bullet->SetIsActiveFalse();
	}

	

	Bullet* Game::GetBulletFromPool()
	{
		for (int i = 0; i < BULLET_POOL_SIZE; i++)
		{
			if (m_Bullet[i]->IsActive() == false)
			{
				return m_Bullet[i];
			}
		}

		return nullptr;
	}

	void Game::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{
		m_Player->OnKeyEvent( keyCode, keyState );
	}

	void Game::OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY)
	{		
	}

	void Game::OnMouseMovedEvent(float mouseX, float mouseY)
	{
	}


}