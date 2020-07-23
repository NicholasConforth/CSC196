#include "Projectile.h"
#include "Graphics/ParticleSystem.h"


    bool Projectile::Load(const std::string& filename)
    {
        bool success = false;

        std::ifstream stream(filename);
        if (stream.is_open())
        {
            success = true;

            // load the base actor members
            Actor::Load(stream);

            // stream into thrust
            std::string line;
            std::getline(stream, line);
            m_thrust = stof(line);
            

            stream.close();
        }

        return success;

    }

    void Projectile::Update(float dt)
    {
        lifetime -= dt;
        m_destroy = (lifetime <= 0);
        nc::Vector2 direction = nc::Vector2::Rotatate(nc::Vector2::forward, m_transform.angle);
        nc::Vector2 velocity = direction.Normalized() * m_thrust;
        m_transform.position = m_transform.position + velocity * dt;
        g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20.0f, 1.0f, nc::Color::yellow, 1.0f, 100.0f, 200.0f);
        m_transform.Update();
    }

    void Projectile::OnCollision(Actor* actor)
    {
        if (actor->GetType() == eType::ENEMY) 
        {
            m_destroy = true;
        }
    }
