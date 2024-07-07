#pragma once

#include <GameDev2D.h>

namespace GameDev2D
{
    // Asteroid class handles functionalities related to the asteroid,
    // including movement, rendering, and collision.
    class Asteroid
    {
    public:
        // Constructor for the Asteroid.
        Asteroid();

        // Update the asteroid's state, including position and rotation.
        void OnUpdate(float delta);

        // Render the asteroid graphics to the screen.
        void OnRender(BatchRenderer& batchRenderer);

        // Getter for the asteroid's maximum radius.
        float GetMaxRadius() const;

        // Setter for the asteroid's maximum radius.
        void SetMaxRadius(float radius);

        // Getter for the asteroid's current position.
        Vector2 GetPosition() const;

        // Check if the asteroid is currently active.
        bool IsActive() const;

        // Set the asteroid's active state to false.
        void SetIsActiveFalse();

    private:
        // Initialize the shape of the asteroid.
        void InitializeShape();

        // Initialize the position of the asteroid.
        void InitializePosition();

        // Initialize the velocity and angular velocity of the asteroid.
        void InitializeVelocity();

        // Wrap the asteroid's position around the screen edges.
        void WrapPosition();

        Vector2 m_Velocity;   // The current velocity of the asteroid.
        Vector2 m_Position;   // The current position of the asteroid.
        float m_AngularVelocity;   // The angular velocity of the asteroid.
        float m_Angle;   // The current angle of the asteroid.
        float m_MaxRadius;   // The maximum radius of the asteroid.
        std::vector<Vector2> m_Shape;   // The graphical representation of the asteroid.
        bool m_IsActive;   // Whether the asteroid is currently active.
    };
}
