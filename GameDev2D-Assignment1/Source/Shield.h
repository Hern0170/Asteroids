#pragma once

#include <GameDev2D.h>

namespace GameDev2D
{
    // Shield class handles the functionalities related to the shield,
    // including activation, updating, and rendering.
    class Shield
    {
    public:
        // Constructors for the Shield, one with a specified position and one with a default position.
        Shield(const Vector2& position);
        Shield();

        // Update the shield's state, including timing and position wrapping.
        void OnUpdate(float delta);

        // Render the shield graphics to the screen.
        void OnRender(BatchRenderer& batchRenderer);

        // Getter for the shield's collision radius.
        float GetRadius() const;

        // Getter for the shield's current position.
        Vector2 GetPosition() const;

        // Check if the shield is currently active.
        bool IsActive() const;

        // Set the shield's active state to false.
        void SetIsActiveFalse();

        // Set the shield's active state to true.
        void SetIsActiveTrue();

        // Activate the shield at a specific position.
        void Activate(const Vector2& position);

    private:
        // Initialize the shape of the shield.
        void InitializeShape();

        // Update the shield's active timer.
        void UpdateShieldTimer(float delta);

        // Wrap the shield's position around the screen edges.
        void WrapPosition();

        Vector2 m_Position;   // The current position of the shield.
        std::vector<Vector2> m_Shape;  // The graphical representation of the shield.
        float m_Angle;   // The angle of the shield.
        bool m_IsActive;   // Whether the shield is currently active.

        float m_Radius;   // The collision radius of the shield.
        float m_ShieldTimer;   // Timer tracking how long the shield has been active.
    };
}
