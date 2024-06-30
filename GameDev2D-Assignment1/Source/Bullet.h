#pragma once
#include <GameDev2D.h>
#include "Constants.h"
#include "Player.h"



namespace GameDev2D
{
    class Bullet
    {
    public:
        Bullet(const Vector2& position, const Vector2& velocity);
        Bullet();

        void OnUpdate(float delta);
        void OnRender(BatchRenderer& batchRenderer);

        Vector2 GetPosition() const;
        float GetRadius() const;   
        bool IsActive() const;
        void Activate(const Vector2& position, const Vector2& velocity);
        void Activate(const Vector2& position, const Vector2& velocity, const GameDev2D::Color color, float size);
        void  SetIsActiveFalse();
        
    private:
        Vector2 m_Position;
        Vector2 m_Velocity;
        float m_Radius;
        bool m_IsActive;
        float m_BulletTimer;
        GameDev2D::Color m_Color;


    };

}


