#include "Asteroid.h"
#include "Constants.h"

namespace GameDev2D
{
    Asteroid::Asteroid() :
        m_Velocity(Vector2::Zero),
        m_Position(Vector2::Zero),
        m_AngularVelocity(0.0f),
        m_Angle(0.0f),
        m_MaxRadius(0.0f),
        m_IsActive(true)
    {
        InitializeShape();
        InitializePosition();
        InitializeVelocity();
    }

    void Asteroid::InitializeShape()
    {
        int numSides = Math::RandomInt(ASTEROID_MIN_SIDES, ASTEROID_MAX_SIDES);
        float radiansPerSide = 2.0f * static_cast<float>(M_PI) / static_cast<float>(numSides);

        for (int i = 0; i < numSides; i++) {
            float radius = Math::RandomFloat(ASTEROID_MIN_RADIUS, ASTEROID_MAX_RADIUS);
            float angle = i * radiansPerSide;

            if (radius > m_MaxRadius) {
                m_MaxRadius = radius;
            }

            m_Shape.push_back(Vector2(cos(angle), sin(angle)) * radius);
        }

        m_Shape.push_back(m_Shape[0]);
    }

    void Asteroid::InitializePosition()
    {
        if (Math::RandomInt(0, 1) == 0) {
            m_Position.x = Math::RandomFloat(0, static_cast<float>(GameDev2D::GetScreenWidth()));
            m_Position.y = static_cast<float>(Math::RandomInt(0, 1)) * GameDev2D::GetScreenHeight();
        }
        else {
            m_Position.x = static_cast<float>(Math::RandomInt(0, 1)) * GameDev2D::GetScreenWidth();
            m_Position.y = Math::RandomFloat(0, static_cast<float>(GameDev2D::GetScreenHeight()));
        }
    }

    void Asteroid::InitializeVelocity()
    {
        float radians = Math::RandomFloat(0, static_cast<float>(M_PI) * 2);
        float speed = Math::RandomFloat(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
        Vector2 direction = Vector2(cos(radians), sin(radians));
        m_Velocity = direction * speed;
        m_AngularVelocity = Math::RandomFloat(ASTEROID_MIN_ANGULAR_VELOCITY, ASTEROID_MAX_ANGULAR_VELOCITY);
    }

    void Asteroid::OnUpdate(float delta)
    {
        m_Angle += m_AngularVelocity * delta;
        m_Position += m_Velocity * delta;
        WrapPosition();
    }

    void Asteroid::WrapPosition()
    {
        if (m_Position.x < -m_MaxRadius) {
            m_Position.x += GameDev2D::GetScreenWidth() + m_MaxRadius * 2.0f;
        }
        if (m_Position.x >= GameDev2D::GetScreenWidth() + m_MaxRadius) {
            m_Position.x -= GameDev2D::GetScreenWidth() + m_MaxRadius * 2.0f;
        }
        if (m_Position.y < -m_MaxRadius) {
            m_Position.y += GameDev2D::GetScreenHeight() + m_MaxRadius * 2.0f;
        }
        if (m_Position.y >= GameDev2D::GetScreenHeight() + m_MaxRadius) {
            m_Position.y -= GameDev2D::GetScreenHeight() + m_MaxRadius * 2.0f;
        }
    }

    void Asteroid::OnRender(BatchRenderer& batchRenderer)
    {
        if (m_IsActive) {
            batchRenderer.RenderLineStrip(m_Shape, GameDev2D::Color::Random(), 2, m_Position, m_Angle);
        }
    }

    float Asteroid::GetMaxRadius() const
    {
        return m_MaxRadius;
    }

    void Asteroid::SetMaxRadius(float radius)
    {
        m_MaxRadius = radius;
    }

    Vector2 Asteroid::GetPosition() const
    {
        return m_Position;
    }

    bool Asteroid::IsActive() const
    {
        return m_IsActive;
    }

    void Asteroid::SetIsActiveFalse()
    {
        m_IsActive = false;
    }
}
