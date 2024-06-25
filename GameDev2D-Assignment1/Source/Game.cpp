#include "Game.h"



namespace GameDev2D
{
	Game::Game() :
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
	}

	void Game::OnRender(BatchRenderer& batchRenderer)
	{
		batchRenderer.BeginScene();
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