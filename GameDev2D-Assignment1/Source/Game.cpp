#include "Game.h"



namespace GameDev2D
{
	Game::Game() :
		m_TextHealth("OpenSans-CondBold_72"),
		m_TextAsteroids("OpenSans-CondBold_72"),
		m_TextWin("OpenSans-CondBold_72"),
		m_TextTime("OpenSans-CondBold_72"),
		m_Timer(0.0f),
		m_asteroidsCount(NUM_ASTEROIDS),
		m_Player(nullptr),
		m_Playing(true),
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

		for (int i = 0; i < SHIELD_POOL_SIZE; i++)
		{
			m_Shield[i] = new Shield();
		}


		m_TextHealth.SetText("Lives: " + std::to_string(m_Player->GetHealth()));
		m_TextAsteroids.SetText("Asteroids: " + std::to_string(m_asteroidsCount));
		m_TextTime.SetText("TIME: " + std::to_string(m_Timer) + " SECONDS");
		m_TextAsteroids.SetPosition(10.0f, 100.0f);
		m_TextTime.SetPosition(static_cast<float>(GetHalfScreenWidth()-300.0f), static_cast<float>(GetHalfScreenHeight()));
		m_TextWin.SetPosition(GetHalfScreenWidth()-300.0f, GetHalfScreenHeight()+100.0f);

		m_TextWin.SetText("YOU WIN!");
		

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

		for (int i = 0; i < SHIELD_POOL_SIZE; i++)
		{
			if (m_Shield[i] != nullptr)
			{
				delete m_Shield[i];
				m_Shield[i] = nullptr;
			}
		}

	}

	void Game::OnUpdate(float delta)
	{
		
		if (m_Playing) 
		{
			if (m_asteroidsCount > 0) {
				m_Timer += delta; 
			}
			else {
				m_Playing = false; 
				End();  
			}


			m_Player->OnUpdate( delta );
		
			for (unsigned int i = 0; i < m_Asteroids.size(); i++)
			{
				m_Asteroids.at(i).OnUpdate( delta );
			}

			for (int i = 0; i < BULLET_POOL_SIZE; i++)
			{
				m_Bullet[i]->OnUpdate(delta);
			}

			for (int i = 0; i <SHIELD_POOL_SIZE; i++)
			{
				m_Shield[i]->OnUpdate(delta);
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

			for (auto& shield : m_Shield) {
				if (!shield->IsActive()) continue;
					if (CheckCollision(shield,m_Player)) {
						Player_ShieldCollision(m_Player, shield);
					}
			}
		}

	}

	void Game::OnRender(BatchRenderer& batchRenderer)
	{
		batchRenderer.BeginScene();
		if (m_asteroidsCount == 0 )
		{
			m_Playing = false;
			End();
			batchRenderer.RenderSpriteFont(m_TextWin);
			batchRenderer.RenderSpriteFont(m_TextTime);

		}

		if (m_Playing)
		{
			batchRenderer.RenderSpriteFont(m_TextHealth);
			batchRenderer.RenderSpriteFont(m_TextAsteroids);

		
		
			for (int i = 0; i < BULLET_POOL_SIZE; i++)
			{
				m_Bullet[i]->OnRender(batchRenderer);
			}


			m_Player->OnRender( batchRenderer );


			for (unsigned int i = 0; i < m_Asteroids.size(); i++)
			{
				m_Asteroids.at(i).OnRender( batchRenderer );
			}

			for (int i = 0; i < SHIELD_POOL_SIZE; i++)
			{
				m_Shield[i]->OnRender(batchRenderer);
			}
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

	void Game::SpawnShield(const Vector2& position)
	{
			Shield* shield = GetShieldFromPool();
		if (shield != nullptr)
		{
			shield->Activate(position);
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

	bool Game::CheckCollision(const Shield* shield, const Player* player)
	{
		if (!shield->IsActive() ) return false; 
		Vector2 diff = player->GetPosition() - shield->GetPosition();
		float distanceSquared = diff.LengthSquared();
		float radiiSum = player->GetRadius() + shield->GetRadius();
		return distanceSquared <= (radiiSum * radiiSum);
	}

	bool Game::CheckCollision(const Shield* shield, const Asteroid* asteroid)
	{
		if (!shield->IsActive() || !asteroid->IsActive()) return false;

		Vector2 diff = shield->GetPosition() - asteroid->GetPosition();
		float distanceSquared = diff.LengthSquared();
		float radiiSum = shield->GetRadius() + asteroid->GetMaxRadius();
		return distanceSquared <= (radiiSum * radiiSum);
	}

	void Game::Player_AsteroidCollision(Player* player, Asteroid& asteroid)
	{
		if (player->CanBeHit() && asteroid.IsActive()) {  

			if (player->GetHealth() == 2)
			{
				asteroid.SetIsActiveFalse();
				m_asteroidsCount--;
				m_TextAsteroids.SetText("Asteroids: " + std::to_string(m_asteroidsCount));
			}
			player->SetHealth(player->GetHealth() - 1); 
			if (player->GetHealth() < 1) {

				player->SetPosition();
				player->SetHealth(1);
			
			}
			m_TextHealth.SetText("Lives: " + std::to_string(player->GetHealth()));
			player->ResetCollisionTimer();
		}
		
	}

	void Game::Player_ShieldCollision(Player* player, Shield* shield)
	{
		if (player->GetHealth() == 1) {
			shield->SetIsActiveFalse();
			player->SetHealth(player->GetHealth() + 1);
			m_TextHealth.SetText("Lives: " + std::to_string(player->GetHealth()));

		}
		

	}

	void Game::Bullet_AsteroidCollision(Bullet* bullet, Asteroid& asteroid)
	{
		
		asteroid.SetIsActiveFalse();
		bullet->SetIsActiveFalse();
		m_asteroidsCount--;
		m_TextAsteroids.SetText("Asteroids: " + std::to_string(m_asteroidsCount));
		if (Math::RandomInt(1, 7) == 7 && m_Player->GetHealth() <= 2)
		{
			SpawnShield(asteroid.GetPosition());

		}

		
	}

	void Game::End()
	{
		int timeInSeconds = static_cast<int>(m_Timer);  // Convertir m_Timer a segundos enteros
		m_TextTime.SetText("TIME: " + std::to_string(timeInSeconds) + " SECONDS");
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

	Shield* Game::GetShieldFromPool()
	{
		for (int i = 0; i < SHIELD_POOL_SIZE; i++)
		{
			if (m_Shield[i]->IsActive() == false)
			{
				return m_Shield[i];
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