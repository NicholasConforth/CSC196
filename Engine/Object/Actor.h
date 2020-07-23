#pragma once
#include "../Math/Transform.h"
#include "../Graphics/shape.h"

namespace nc 
{
	class Scene;

	class Actor
	{
	public:
		enum class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE
		};
	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {};  // make sure to initialize m_transform and m_shape;
		virtual ~Actor() {}

		virtual eType GetType() = 0;

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

		void SetScene(Scene* scene) { m_scene = scene; }

		float GetRadius();

		Transform& GetTransform() { return m_transform; } // return the transform
		Shape& GetShape() { return m_shape; } // return the shape

		void SetDestroy(bool destroy = true) { m_destroy = destroy; }
		bool ISDestroy() { return m_destroy; }
	protected:
		bool m_destroy{ false };
		class Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;
	};
}
