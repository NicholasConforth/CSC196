#pragma once
#include <vector>
#include"core.h"
#include "..\Math\Vector2.h"
#include "..\Math\Color.h"
#include "..\Math\Transform.h"
#include <string>

namespace nc
{
	struct Shape
	{
	public:
		Shape() {}
		Shape(const std::vector<nc::Vector2>& points, const Color& color) : m_points{ points }, m_color{ color } {} ;

		bool load(const std::string& filename);

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale = 1.0f, float angle = 0.0f);
		void Draw(Core::Graphics& graphics, const Transform transform);
	

		void SetColor(Color color) { m_color = color; };
		const Color& GetColor() const { return m_color; };

		float GetRadius() { return m_radius; }
	private:
		std::vector<nc::Vector2> m_points;
		Color m_color;
		float m_radius;
	};
}



