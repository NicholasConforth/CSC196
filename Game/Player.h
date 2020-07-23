#pragma once
#include "Object/Actor.h"
#include "Math/Vector2.h"
#include "Math/MathStuff.h"
#include <fstream>

	class Player : public nc::Actor
	{
	public:
		Player() {}
		virtual ~Player() {}

		virtual eType GetType() { return eType::PLAYER; }

		virtual bool Load(const std::string& filename);

		virtual void Update(float dt);

		void OnCollision(Actor* actor);
		//virtual void Draw(Core::Graphics& graphics);
	protected:
	
		float m_thrust{ 400.0f };
	
		float m_rotationrate{ 0 };
	
		float m_firerate{ 0.2f };
		float m_firetimer{ 0.0f };

		nc::Vector2 m_velocity;
	};