#pragma once

#include <GameDev2D.h>
#include "Constants.h"
#include "Player.h"

namespace GameDev2D
{
    // Bullet class handles functionalities related to the bullet,
    // including activation, updating, and rendering.
    class Bullet
    {
    public:
        // Constructors for the Bullet, one with a specified position and velocity, and one with default values.
        Bullet(const Vector2& position, const Vector2& velocity);
        Bullet();

        // Update the bullet's state, including position and active status.
        void OnUpdate(float delta);

        // Render the bullet graphics to the screen.
        void OnRender(BatchRenderer& batchRenderer);

        // Getter for the bullet's current position.
        Vector2 GetPosition() const;

        // Getter for the bullet's collision radius.
        float GetRadius() const;

        // Check if the bullet is currently active.
        bool IsActive() const;

        // Activate the bullet with a specific position and velocity.
        void Activate(const Vector2& position, const Vector2& velocity);

        // Activate the bullet with a specific position, velocity, color, and size.
        void Activate(const Vector2& position, const Vector2& velocity, const GameDev2D::Color color, float size);

        // Set the bullet's active state to false.
        void SetIsActiveFalse();

    private:
        // Initialize the bullet properties.
        void Initialize(const Vector2& position, const Vector2& velocity, const GameDev2D::Color color, float size, bool isActive);

        // Update the bullet's active timer.
        void UpdateBulletTimer(float delta);

        // Wrap the bullet's position around the screen edges.
        void WrapPosition();

        Vector2 m_Position;   // The current position of the bullet.
        Vector2 m_Velocity;   // The current velocity of the bullet.
        float m_Radius;   // The collision radius of the bullet.
        bool m_IsActive;   // Whether the bullet is currently active.
        float m_BulletTimer;   // Timer tracking how long the bullet has been active.
        GameDev2D::Color m_Color;   // The color of the bullet.
    };
}
