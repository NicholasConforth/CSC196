#include "Enemy.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include"Math/MathStuff.h"
#include "../Game/Game.h"



    bool Enemy::Load(const std::string& filename)
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

    void Enemy::Update(float dt)
    {
        nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
        nc::Vector2 enemyVelocity = direction.Normalized() * 0;
        m_transform.position = m_transform.position + enemyVelocity * dt;
        m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);
        m_transform.Update();
    }

    void Enemy::OnCollision(Actor* actor)
    {
        if (actor->GetType() == eType::PROJECTILE)
        {
            m_destroy = true;

            m_scene->GetGame()->AddPoints(100);
            
            nc::Color colors[] = { nc::Color::white, nc::Color::blue, nc::Color::yellow };
            nc::Color color = colors[rand() % 3];
            g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
        }
    }
