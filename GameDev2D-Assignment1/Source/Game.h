#pragma once

#include <GameDev2D.h>
#include <vector>
#include <iostream>

#include "Player.h"
#include "Asteroid.h"
#include "Constants.h"
#include "Shield.h"

namespace GameDev2D
{
    // Game class handles the main game loop, including updating and rendering game objects,
    // handling input events, and managing game state.
    class Game
    {
    public:
        // Constructor and destructor for the Game class.
        Game();
        ~Game();

        // Update game logic in the OnUpdate method.
        void OnUpdate(float delta);

        // Render game objects in the OnRender method.
        void OnRender(BatchRenderer& batchRenderer);

        // Input event methods.
        void OnKeyEvent(KeyCode keyCode, KeyState keyState);
        void OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY);
        void OnMouseMovedEvent(float mouseX, float mouseY);

        // Methods to spawn bullets and shields.
        void SpawnBullet(const Vector2& position, const Vector2& velocity);
        void SpawnBullet(const Vector2& position, const Vector2& velocity, const GameDev2D::Color color, float size);
        void SpawnShield(const Vector2& position);

        // Collision check methods.
        bool CheckCollision(const Player* player, const Asteroid* asteroid);
        bool CheckCollision(const Bullet* bullet, const Asteroid* asteroid);
        bool CheckCollision(const Shield* shield, const Player* player);
        bool CheckCollision(const Shield* shield, const Asteroid* asteroid);

        // Collision handling methods.
        void Player_AsteroidCollision(Player* player, Asteroid& asteroid);
        void Player_ShieldCollision(Player* player, Shield* shield);
        void Bullet_AsteroidCollision(Bullet* bullet, Asteroid& asteroid);

        // Game state methods.
        bool GetPlaying();
        bool GetIsShooting();
        void StopSound();
        void End();

    private:
        // Initialize the asteroids.
        void InitializeAsteroids();

        // Initialize the bullet pool.
        void InitializeBulletPool();

        // Initialize the shield pool.
        void InitializeShieldPool();

        // Initialize text elements.
        void InitializeText();

        // Initialize sound effects.
        void InitializeSounds();

        // Cleanup bullet pool memory.
        void CleanupBulletPool();

        // Cleanup shield pool memory.
        void CleanupShieldPool();

        // Update the intro state.
        void UpdateIntroState(float delta);

        // Update the playing state.
        void UpdatePlayingState(float delta);

        // Check all collisions.
        void CheckCollisions();

        // Render the intro state.
        void RenderIntroState(BatchRenderer& batchRenderer);

        // Render the playing state.
        void RenderPlayingState(BatchRenderer& batchRenderer);

        // Get a bullet or shield from the pool.
        Bullet* GetBulletFromPool();
        Shield* GetShieldFromPool();

        Player* m_Player; // Player object.
        std::vector<Asteroid> m_Asteroids; // Vector of asteroid objects.

        bool m_IsShooting; // Flag to track if shooting is active.

        Shield* m_Shield[SHIELD_POOL_SIZE]; // Array of shield objects.
        Bullet* m_Bullet[BULLET_POOL_SIZE]; // Array of bullet objects.

        // Text elements for the UI.
        SpriteFont m_TextHealth;
        SpriteFont m_TextAsteroids;
        SpriteFont m_TextWin;
        SpriteFont m_TextTime;
        SpriteFont m_TextIntro;
        SpriteFont m_TextStart;
        SpriteFont m_TextAutor;

        float m_Timer; // Game timer.
        int m_asteroidsCount; // Count of remaining asteroids.
        bool m_Playing; // Flag to track if the game is currently being played.
        bool m_Intro; // Flag to track if the game is in the intro state.

        float m_StartTimer; // Timer for the start state.
        bool m_StartToggle; // Toggle for start state UI.

        // Sound effects for various game events.
        Audio m_SoundMenu;
        Audio m_SoundStart;
        Audio m_SoundGame;
        Audio m_SoundCollisionAsteroidA;
        Audio m_SoundCollisionAsteroidB;
        Audio m_SoundCollisionAsteroidC;
        Audio m_SoundCollisionShield;
        Audio m_SoundSpawnShield;
        Audio m_SoundTakenShield;
        Audio m_SoundWin;
    };
}
