#pragma once
#include <GameDev2D.h>
#include "Constants.h"
namespace GameDev2D
{
    class Bullet
    {
    public:
        Bullet(const Vector2& position, const Vector2& velocity);
        Bullet();

        void OnUpdate(float delta);
        void OnRender(BatchRenderer& batchRenderer);

        Vector2 GetPosition();
        bool IsActive();
        void Activate(const Vector2& position, const Vector2& velocity);
    private:
        Vector2 m_Position;
        Vector2 m_Velocity;
        float m_Radius;
        bool m_Active;
        float m_BulletTimer;
    };

}


