#include "Game.h"
#include "Constants.h"


namespace GameDev2D
{
	Game::Game() :
		m_Player(),
		m_Asteroids{}
	{
		for( int i = 0; i < NUM_ASTEROIDS; i++ )
		{
			m_Asteroids.push_back(Asteroid());
		}
	}

	Game::~Game()
	{

	}

	void Game::OnUpdate(float delta)
	{
		m_Player.OnUpdate( delta );
		for (unsigned int i = 0; i < m_Asteroids.size(); i++)
		{
			m_Asteroids.at(i).OnUpdate( delta );
		}
	}

	void Game::OnRender(BatchRenderer& batchRenderer)
	{
		batchRenderer.BeginScene();

		m_Player.OnRender( batchRenderer );
		for (unsigned int i = 0; i < m_Asteroids.size(); i++)
		{
			m_Asteroids.at(i).OnRender( batchRenderer );
		}

		batchRenderer.EndScene();
	}

	void Game::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{
		m_Player.OnKeyEvent( keyCode, keyState );
	}

	void Game::OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY)
	{		
	}

	void Game::OnMouseMovedEvent(float mouseX, float mouseY)
	{
	}
}