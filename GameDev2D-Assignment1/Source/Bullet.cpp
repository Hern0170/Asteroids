#include "Bullet.h"
namespace GameDev2D
{


    Bullet::Bullet(const Vector2& position, const Vector2& velocity) :
        m_Position(position),
        m_Velocity(velocity),
        m_Radius(1.0f),
       m_Active(false)
    {
    }

    Bullet::Bullet() :
        m_Position(Vector2::Zero),
        m_Velocity(Vector2::Zero),
        m_Active(false),
        m_Radius(1.0f)
    {
    }


    void Bullet::OnUpdate(float delta)
    {
        if (m_Active) {
            this->m_Position += m_Velocity * delta;

            m_BulletTimer += delta;
            if (m_BulletTimer >= BULLET_TIME_ACTIVE) {
                m_Active = false;
                m_BulletTimer = 0.0f;
            }


            if (m_Position.x < 0)
            {
                m_Position.x += GameDev2D::GetScreenWidth();
            }

            if (m_Position.x >= GameDev2D::GetScreenWidth())
            {
                m_Position.x -= GameDev2D::GetScreenWidth();
            }

            if (m_Position.y < 0)
            {
                m_Position.y += GameDev2D::GetScreenHeight();
            }

            if (m_Position.y >= GameDev2D::GetScreenHeight())
            {
                m_Position.y -= GameDev2D::GetScreenHeight();
            }
            


        }
    }

    void Bullet::OnRender(BatchRenderer& batchRenderer)
    {
        if (m_Active)
        {
            batchRenderer.RenderCircle(m_Position.x, m_Position.y, m_Radius + BULLET_RADIUS_INC, ColorList::Blue);

            batchRenderer.RenderCircle(m_Position.x, m_Position.y, m_Radius, ColorList::LightBlue);
        }

    }

    Vector2 Bullet::GetPosition()
    {
        return m_Position;
    }
    bool Bullet::IsActive()
    {
        return m_Active;
    }
    void Bullet::Activate(const Vector2& position, const Vector2& velocity)
    {
            m_Position = position;
            m_Velocity = velocity;
            m_Active = true;
            m_BulletTimer = 0.0f;
    }
}