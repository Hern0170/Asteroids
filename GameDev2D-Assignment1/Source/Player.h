#pragma once

#include <GameDev2D.h>
#include "Bullet.h"

namespace GameDev2D
{
    class Game; // Forward declaration of Game to avoid circular dependency.

    // Player class handles all functionalities related to the game's player,
    // including movement, shooting, and collision handling.
    class Player
    {
    public:
        // Constructor initializing player properties and linking to the game object.
        Player(Game* game);

        // Update player state, handle movement, shooting, and collision logic.
        void OnUpdate(float delta);

        // Render player graphics to the screen.
        void OnRender(BatchRenderer& batchRenderer);

        // Handle keyboard inputs to control the player.
        void OnKeyEvent(KeyCode keyCode, KeyState keyState);

        // Functionality to shoot projectiles from the player's current position and orientation.
        void Shoot();

        // Getter for player's collision radius.
        float GetRadius() const;

        // Getter for player's current position.
        Vector2 GetPosition() const;

        // Getter for player's current health.
        int GetHealth() const;

        // Setter for player's health.
        void SetHealth(int h);

        // Reset the timer tracking time since last hit.
        void ResetCollisionTimer();

        // Check if the player can currently be hit based on collision cooldown.
        bool CanBeHit() ;

        // Activate and deactivate the player's defensive shield.
        void ActivateShield();
        void DeactivateShield();

        // Set the player's position randomly within the game screen.
        void SetPosition();

        // Check if the player's special attack is charged and ready.
        bool GetCharged() ;

        // Stop all sound effects associated with the player.
        void StopSoundPlayer();

    private:
        // Initialize player graphics components like the shape and flame effects.
        void InitializeGraphics();

        // Initialize player-related sounds.
        void InitializeSounds();

        void InitializeShields();

        // Detailed graphics setup for the player's shape.
        void InitializeShape();

        // Setup for flame graphics used when the player is moving.
        void InitializeFlame();
        // Update for flame interval
        void FlameInterval(float delta);

        // Update handling for collision cooldown logic.
        void UpdateCollisionCooldown(float delta);

        // Update the orbit of the shield around the player.
        void UpdateShieldOrbit(float delta);

        // Handle mechanics related to burst and charged shooting modes.
        void ProcessShootingMechanics(float delta);

        // Specific handling for burst shooting.
        void HandleBurstShooting(float delta);

        // Specific handling for charged shooting.
        void HandleChargedShooting(float delta);

        // Update player movement and handle screen wrapping.
        void UpdateMovementAndScreenWrapping(float delta);

        // Helper function to wrap player position around screen edges.
        void WrapPosition();

        // Render helper functions.
        void RenderShield(BatchRenderer& batchRenderer);
        void RenderFlame(BatchRenderer& batchRenderer);
        void RenderShip(BatchRenderer& batchRenderer);

        Game* m_Game; // Game context to access global features.

        // Player properties
        Vector2 m_Velocity;
        Vector2 m_Position;
        float m_Angle;
        float m_Radius;
        Vector2 m_Controls;

        // Graphical representations
        std::vector<Vector2> m_Shape;
        std::vector<Vector2> m_Flame;
        bool m_FlameColorToggle;
        float m_FlameTimer;

        // Shield and health properties
        bool m_ShieldActive;
        int m_PlayerHealth;
        float m_CollisionCooldown;
        float m_TimeSinceLastHit;
        float m_OrbitRadius;
        float m_Radians[3];  // Array for shield particle positioning.
        float m_AngularVelocity;

        // Shooting properties
        bool m_Burst;
        bool m_Charged;
        bool m_FireLeft;
        bool m_BurstActive;
        float m_TimerShoot;
        float m_TimerChargedShoot;
        int m_BurstFireCount;

        // Sound effects for various actions
        Audio m_SoundBasicShoot;
        Audio m_SoundBurstShoot;
        Audio m_SoundChargedShoot;
        Audio m_SoundPlayerMove;
    };
}

