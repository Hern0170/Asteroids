#include "Game.h"

namespace GameDev2D
{
    Game::Game() :
        m_TextAsteroids("OpenSans-CondBold_72"),
        m_TextWin("OpenSans-CondBold_72"),
        m_TextTime("OpenSans-CondBold_72"),
        m_TextIntro("OpenSans-CondBold_72"),
        m_TextAutor("OpenSans-CondBold_72"),
        m_TextStart("OpenSans-CondBold_72"),
        m_Timer(0.0f),
        m_asteroidsCount(NUM_ASTEROIDS),
        m_Player(nullptr),
        m_Playing(false),
        m_IsShooting(false),
        m_Intro(true),
        m_StartToggle(true),
        m_StartTimer(0.0f),
        m_Asteroids{},
        m_SoundMenu("Loop"),
        m_SoundStart("Start"),
        m_SoundGame("Space"),
        m_SoundCollisionAsteroidA("Explosion_A"),
        m_SoundCollisionAsteroidB("Explosion_B"),
        m_SoundCollisionAsteroidC("Explosion_C"),
        m_SoundCollisionShield("ShieldCollision"),
        m_SoundSpawnShield("ShieldSpawn"),
        m_SoundTakenShield("ShieldTaken"),
        m_SoundWin("Win")
    {
        m_Player = new Player(this);
        InitializeAsteroids();
        InitializeBulletPool();
        InitializeShieldPool();
        InitializeText();
        InitializeSounds();
    }

    Game::~Game()
    {
        if (m_Player != nullptr)
        {
            delete m_Player;
            m_Player = nullptr;
        }

        CleanupBulletPool();
        CleanupShieldPool();
    }

    void Game::InitializeAsteroids()
    {
        for (int i = 0; i < NUM_ASTEROIDS; i++)
        {
            m_Asteroids.push_back(Asteroid());
        }
    }

    void Game::InitializeBulletPool()
    {
        for (int i = 0; i < BULLET_POOL_SIZE; i++)
        {
            m_Bullet[i] = new Bullet();
        }
    }

    void Game::InitializeShieldPool()
    {
        for (int i = 0; i < SHIELD_POOL_SIZE; i++)
        {
            m_Shield[i] = new Shield();
        }
    }

    void Game::InitializeText()
    {
        m_TextIntro.SetText("ASTEROID HUNTER\n");
        m_TextIntro.SetPosition(static_cast<float>(GetHalfScreenWidth() - TEXT_POS_X), static_cast<float>(GetHalfScreenHeight()));

        m_TextAutor.SetText("BY GABRIEL\n  \n ");
        m_TextAutor.SetPosition(static_cast<float>(GetHalfScreenWidth() - TEXT_POS_X), static_cast<float>(GetHalfScreenHeight() + TEXT_POS_Y_NAME));
        m_TextAutor.SetScale(TEXT_SIZE_NAME, TEXT_SIZE_NAME);

        m_TextStart.SetText("\n\n\n\nPRESS ENTER TO START");
        m_TextStart.SetPosition(static_cast<float>(GetHalfScreenWidth() - TEXT_POS_X_START), static_cast<float>(GetHalfScreenHeight() - TEXT_POS_Y));
        m_TextStart.SetColor(GameDev2D::ColorList::SlateGray);
        m_TextStart.SetScale(TEXT_SIZE_START, TEXT_SIZE_START);

        m_TextAsteroids.SetText("Asteroids: " + std::to_string(m_asteroidsCount));
        m_TextAsteroids.SetPosition(TEXT_POS_Y_NAME, TEXT_POS_Y);

        m_TextTime.SetText("TIME: " + std::to_string(m_Timer) + " SECONDS");
        m_TextTime.SetPosition(static_cast<float>(GetHalfScreenWidth() - TEXT_POS_X), static_cast<float>(GetHalfScreenHeight()));
        m_TextWin.SetPosition(GetHalfScreenWidth() - TEXT_POS_X, GetHalfScreenHeight() + TEXT_POS_Y);
        m_TextWin.SetText("YOU WIN!");
    }

    void Game::InitializeSounds()
    {
        m_SoundMenu.SetVolume(SOUND_VOLUME);
        m_SoundStart.SetVolume(SOUND_VOLUME);
        m_SoundGame.SetVolume(SOUND_VOLUME);
        m_SoundCollisionAsteroidA.SetVolume(SOUND_VOLUME);
        m_SoundCollisionAsteroidB.SetVolume(SOUND_VOLUME);
        m_SoundCollisionAsteroidC.SetVolume(SOUND_VOLUME);
        m_SoundCollisionShield.SetVolume(SOUND_VOLUME);
        m_SoundSpawnShield.SetVolume(SOUND_VOLUME);
        m_SoundTakenShield.SetVolume(SOUND_VOLUME);
        m_SoundWin.SetVolume(SOUND_VOLUME);

        m_SoundStart.DoesLoop();
        m_SoundMenu.DoesLoop();
        m_SoundMenu.Play();

        m_SoundGame.SetDoesLoop(true);
        m_SoundWin.SetDoesLoop(false);
    }

    void Game::CleanupBulletPool()
    {
        for (int i = 0; i < BULLET_POOL_SIZE; i++)
        {
            if (m_Bullet[i] != nullptr)
            {
                delete m_Bullet[i];
                m_Bullet[i] = nullptr;
            }
        }
    }

    void Game::CleanupShieldPool()
    {
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
        if (m_Intro)
        {
            UpdateIntroState(delta);
        }

        if (m_Playing)
        {
            UpdatePlayingState(delta);
        }
    }

    void Game::UpdateIntroState(float delta)
    {
        m_SoundMenu.Play();
        m_SoundMenu.DoesLoop();

        m_StartTimer += delta;
        if (m_StartTimer >= 1.0f)
        {
            m_StartToggle = !m_StartToggle;
            m_StartTimer = 0.0f;
        }
    }

    void Game::UpdatePlayingState(float delta)
    {
        if (m_asteroidsCount > 0)
        {
            m_Timer += delta;
        }
        else
        {
            m_Playing = false;
            End();
        }

        m_Player->OnUpdate(delta);

        for (Asteroid& asteroid : m_Asteroids)
        {
            asteroid.OnUpdate(delta);
        }

        for (int i = 0; i < BULLET_POOL_SIZE; i++)
        {
            m_Bullet[i]->OnUpdate(delta);
        }

        for (int i = 0; i < SHIELD_POOL_SIZE; i++)
        {
            m_Shield[i]->OnUpdate(delta);
        }

        CheckCollisions();
    }

    void Game::CheckCollisions()
    {
        for (Asteroid& asteroid : m_Asteroids)
        {
            if (CheckCollision(m_Player, &asteroid))
            {
                Player_AsteroidCollision(m_Player, asteroid);
            }
        }

        for (auto& bullet : m_Bullet)
        {
            if (!bullet->IsActive()) continue;
            for (auto& asteroid : m_Asteroids)
            {
                if (CheckCollision(bullet, &asteroid))
                {
                    Bullet_AsteroidCollision(bullet, asteroid);
                }
            }
        }

        for (auto& shield : m_Shield)
        {
            if (!shield->IsActive()) continue;
            if (CheckCollision(shield, m_Player))
            {
                Player_ShieldCollision(m_Player, shield);
            }
        }
    }

    void Game::OnRender(BatchRenderer& batchRenderer)
    {
        batchRenderer.BeginScene();
        if (m_Intro)
        {
            RenderIntroState(batchRenderer);
        }
        if (m_asteroidsCount == 0)
        {
            End();
            m_Playing = false;
            m_SoundGame.FadeOut(SOUND_VOLUME);
            m_SoundGame.Stop();
            batchRenderer.RenderSpriteFont(m_TextWin);
            batchRenderer.RenderSpriteFont(m_TextTime);
        }

        if (m_Playing)
        {
            RenderPlayingState(batchRenderer);
        }
        batchRenderer.EndScene();
    }

    void Game::RenderIntroState(BatchRenderer& batchRenderer)
    {
        batchRenderer.RenderSpriteFont(m_TextIntro);
        batchRenderer.RenderSpriteFont(m_TextAutor);

        if (m_StartToggle)
        {
            batchRenderer.RenderSpriteFont(m_TextStart);
        }
    }

    void Game::RenderPlayingState(BatchRenderer& batchRenderer)
    {
        //batchRenderer.RenderSpriteFont(m_TextAsteroids);

        for (int i = 0; i < BULLET_POOL_SIZE; i++)
        {
            m_Bullet[i]->OnRender(batchRenderer);
        }

        m_Player->OnRender(batchRenderer);

        for (unsigned int i = 0; i < m_Asteroids.size(); i++)
        {
            m_Asteroids.at(i).OnRender(batchRenderer);
        }

        for (int i = 0; i < SHIELD_POOL_SIZE; i++)
        {
            m_Shield[i]->OnRender(batchRenderer);
        }
    }

    void Game::SpawnBullet(const Vector2& position, const Vector2& velocity)
    {
        Bullet* bullet = GetBulletFromPool();
        if (bullet != nullptr)
        {
            m_IsShooting = true;
            bullet->Activate(position, velocity);
        }
        else
        {
            m_IsShooting = false;
        }
    }

    void Game::SpawnBullet(const Vector2& position, const Vector2& velocity, const GameDev2D::Color color, float size)
    {
        Bullet* bullet = GetBulletFromPool();
        if (bullet != nullptr)
        {
            m_IsShooting = true;
            bullet->Activate(position, velocity, color, size);
        }
        else
        {
            m_IsShooting = false;
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
        if (!shield->IsActive()) return false;
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
        if (player->CanBeHit() && asteroid.IsActive() && !player->GetCharged())
        {
            if (player->GetHealth() == 2)
            {
                m_SoundCollisionShield.Play();
                asteroid.SetIsActiveFalse();
                m_asteroidsCount--;
                m_TextAsteroids.SetText("Asteroids: " + std::to_string(m_asteroidsCount));
            }
            player->SetHealth(player->GetHealth() - PLAYER_HEALTH);
            if (player->GetHealth() < PLAYER_HEALTH)
            {
                player->SetPosition();
                player->SetHealth(PLAYER_HEALTH);
            }
            player->ResetCollisionTimer();
        }
    }

    void Game::Player_ShieldCollision(Player* player, Shield* shield)
    {
        if (player->GetHealth() == PLAYER_HEALTH)
        {
            shield->SetIsActiveFalse();
            player->SetHealth(player->GetHealth() + PLAYER_HEALTH);
            m_SoundTakenShield.Play();
        }
    }

    void Game::Bullet_AsteroidCollision(Bullet* bullet, Asteroid& asteroid)
    {
        int rand = Math::RandomInt(RAND_MIN, RAND_SOUND);
        switch (rand)
        {
        case 1:
        {
            m_SoundCollisionAsteroidA.Play();
            break;
        }
        case 2:
        {
            m_SoundCollisionAsteroidB.Play();
            break;
        }
        case 3:
        {
            m_SoundCollisionAsteroidC.Play();
            break;
        }
        }

        asteroid.SetIsActiveFalse();
        bullet->SetIsActiveFalse();
        m_asteroidsCount--;
        m_TextAsteroids.SetText("Asteroids: " + std::to_string(m_asteroidsCount));

        if (Math::RandomInt(RAND_MIN, RAND_SHIELD) == RAND_SHIELD && m_Player->GetHealth() <= PLAYER_HEALT_MAX)
        {
            m_SoundSpawnShield.Play();
            SpawnShield(asteroid.GetPosition());
        }
    }

    bool Game::GetPlaying()
    {
        return m_Playing;
    }

    bool Game::GetIsShooting()
    {
        return m_IsShooting;
    }

    void Game::StopSound()
    {
        m_SoundMenu.Stop();
        m_SoundStart.Stop();
        m_SoundGame.Stop();
        m_SoundCollisionAsteroidA.Stop();
        m_SoundCollisionAsteroidB.Stop();
        m_SoundCollisionAsteroidC.Stop();
        m_SoundCollisionShield.Stop();
        m_SoundSpawnShield.Stop();
        m_SoundTakenShield.Stop();
        m_Player->StopSoundPlayer();
    }

    void Game::End()
    {
        if (m_Playing)
        {
            m_SoundWin.Play();
            StopSound();
        }

        int timeInSeconds = static_cast<int>(m_Timer);
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
        m_Player->OnKeyEvent(keyCode, keyState);

        if (keyState == KeyState::Down)
        {
            if (keyCode == KeyCode::Enter)
            {
                if (m_Intro)
                {
                    m_SoundStart.Play();
                    m_SoundMenu.Stop();
                    m_SoundGame.SetVolume(SOUND_VOLUME);
                    m_SoundGame.Play();
                    m_Intro = false;
                    m_Playing = true;
                }
            }
        }
    }

    void Game::OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY)
    {
    }

    void Game::OnMouseMovedEvent(float mouseX, float mouseY)
    {
    }
}
