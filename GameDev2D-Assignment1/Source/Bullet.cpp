#include "Bullet.h"
#include "Game.h"

namespace GameDev2D
{

    Bullet::Bullet(const Vector2& position, const Vector2& velocity) :
        m_Position(position),
        m_Velocity(velocity),
        m_Radius(1.0f),
        m_IsActive(false),
        m_Color(BULLET_COLOR)
    {
    }


    Bullet::Bullet() :
        m_Position(Vector2::Zero),
        m_Velocity(Vector2::Zero),
        m_IsActive(false),
        m_Radius(1.0f)
    {
    }


    void Bullet::Initialize(const Vector2& position, const Vector2& velocity, const GameDev2D::Color color, float size, bool isActive)
    {
        m_Position = position;
        m_Velocity = velocity;
        m_Color = color;
        m_Radius = size;
        m_IsActive = isActive;
        m_BulletTimer = 0.0f;
    }


    void Bullet::OnUpdate(float delta)
    {
        if (m_IsActive) {
            m_Position += m_Velocity * delta;
            UpdateBulletTimer(delta);
            WrapPosition();
        }
    }


    void Bullet::UpdateBulletTimer(float delta)
    {
        m_BulletTimer += delta;
        if (m_BulletTimer >= BULLET_TIME_ACTIVE) {
            m_IsActive = false;
            m_BulletTimer = 0.0f;
        }
    }


    void Bullet::WrapPosition()
    {
        if (m_Position.x < 0) {
            m_Position.x += GameDev2D::GetScreenWidth();
        }
        if (m_Position.x >= GameDev2D::GetScreenWidth()) {
            m_Position.x -= GameDev2D::GetScreenWidth();
        }
        if (m_Position.y < 0) {
            m_Position.y += GameDev2D::GetScreenHeight();
        }
        if (m_Position.y >= GameDev2D::GetScreenHeight()) {
            m_Position.y -= GameDev2D::GetScreenHeight();
        }
    }


    void Bullet::OnRender(BatchRenderer& batchRenderer)
    {
        if (m_IsActive) {
            batchRenderer.RenderCircle(m_Position.x, m_Position.y, m_Radius + BULLET_RADIUS_INC, m_Color, ColorList::GhostWhite, BULLET_OUTLINE);
        }
    }


    Vector2 Bullet::GetPosition() const
    {
        return m_Position;
    }


    float Bullet::GetRadius() const
    {
        return m_Radius;
    }


    bool Bullet::IsActive() const
    {
        return m_IsActive;
    }


    void Bullet::Activate(const Vector2& position, const Vector2& velocity)
    {
        Initialize(position, velocity, BULLET_COLOR, m_Radius, true);
    }


    void Bullet::Activate(const Vector2& position, const Vector2& velocity, const GameDev2D::Color color, float size)
    {
        Initialize(position, velocity, color, size, true);
    }

    void Bullet::SetIsActiveFalse()
    {
        m_IsActive = false;
    }
}
