#include "Player.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "../Game/Game.h"
#include "Graphics/ParticleSystem.h"

    bool Player::Load(const std::string& filename)
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
            
             //stream into rotation rate
            std::getline(stream, line);
            m_rotationrate = stof(line);
            
            stream.close();
        }
        return success;
    }

    void Player::Update(float dt)
    {
        m_firetimer += dt;
        if (Core::Input::IsPressed(VK_SPACE) && m_firetimer >= m_firerate)
        {
            m_firetimer;
            Projectile* projectile = new Projectile;
            projectile->Load("Projectile.txt");
            projectile->GetTransform().position = m_transform.position;
            projectile->GetTransform().angle = m_transform.angle;
            m_scene->AddActor(projectile);
        }


        nc::Vector2 force;

        if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
        force = nc::Vector2::Rotatate(force, m_transform.angle);
        m_velocity = m_velocity + (force * dt);
        m_velocity = m_velocity * 0.99f;
        m_transform.position = m_transform.position + (m_velocity * dt);

        // rotate
        if (Core::Input::IsPressed('A')) { m_transform.angle = m_transform.angle - (dt * nc::DegreesToRadians(360.0f)); }
        if (Core::Input::IsPressed('D')) { m_transform.angle = m_transform.angle + (dt * nc::DegreesToRadians(360.0f)); }

        if (m_transform.position.x > 800) m_transform.position.x = 0;
        if (m_transform.position.x < 0) m_transform.position.x = 800;
        if (m_transform.position.y > 600) m_transform.position.y = 0;
        if (m_transform.position.y < 0) m_transform.position.y = 600;


        if (force.Length() > 0)
        {
        g_particleSystem.Create(GetTransform().position, GetTransform().angle + nc::PI, 20.0f, 1.0f, nc::Color::red, 1.0f, 100.0f, 200.0f);
        }

        m_transform.Update();
    }

    void Player::OnCollision(Actor* actor)
    {
        if (actor->GetType() == eType::ENEMY)
        {
            m_scene->GetGame()->SetState(Game::eState::GOMEOVER);
        }
    }

    //void Player::Draw(Core::Graphics& graphics){}
