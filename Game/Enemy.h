#pragma once
#include "Object/Actor.h"
#include "Math/Vector2.h"
#include "Math/MathStuff.h"
#include <fstream>

	class Enemy : public nc::Actor
	{
	public:

		virtual eType GetType() { return eType::ENEMY; }

		virtual bool Load(const std::string& filename);
		virtual void Update(float dt);
		//virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor);

		void SetThrust(float thrust) { m_thrust = thrust; }

		void SetTarget(Actor* actor) { m_target = actor; }

	protected:
		float m_thrust{ 100.0f };
		Actor* m_target{ nullptr };
	};