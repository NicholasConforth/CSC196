#pragma once
#include "Object/Actor.h"
#include "Math/Vector2.h"
#include "Math/MathStuff.h"
#include <fstream>

	class Projectile : public nc::Actor
	{
	public:

		virtual eType GetType() { return eType::PROJECTILE; }

		virtual bool Load(const std::string& filename);

		virtual void Update(float dt);
		//virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor);

		void SetThrust(float thrust) { m_thrust = thrust; }

	protected:
		float m_thrust{ 300.0f };
		Actor* m_target{ nullptr };
		float lifetime{ 3 };
	};