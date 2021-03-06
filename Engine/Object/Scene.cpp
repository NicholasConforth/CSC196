#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include <random>

namespace nc
{
	void Scene::Startup() {}


	void Scene::Shutdown()
	{
		for (nc::Actor* actor : m_actors)
		{
			RemoveActor(actor);
		}
		m_actors.clear();
	}

	void Scene::Update(float dt)
	{
		std::vector<Actor*> actors{ m_actors.begin(), m_actors.end() };
		for (size_t i = 0; i < actors.size(); i++)
		{
			for (size_t j = i + 1; j < actors.size(); j++)
			{
				float distance = Vector2::Distance(actors[i]->GetTransform().position, actors[j]->GetTransform().position);
				if (distance <= 10)
				{
					actors[i]->OnCollision(actors[j]);
					actors[j]->OnCollision(actors[i]);

				}
			}
		}

		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			if ((*iter)->ISDestroy())
			{
				delete* iter;
				iter = m_actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		for (nc::Actor* actor : m_actors)
		{
			actor->Update(dt);
		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		for (nc::Actor* actor : m_actors)
		{
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(Actor* actor)
	{
		actor->SetScene(this);
		m_actors.push_back(actor);
	}

	void Scene::RemoveActor(Actor* actor)
	{
		std::list<Actor*>::iterator iter = std::find(m_actors.begin(), m_actors.end(), actor);
		if (iter != m_actors.end())
		{
			delete* iter;
			m_actors.erase(iter);
		}
	}


}
