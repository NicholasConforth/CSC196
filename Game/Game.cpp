// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "core.h"
#include "Math/MathStuff.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/shape.h"
#include <iostream>
#include <string>

const size_t NUM_POINTS = 40;
float speed = 300.0f;

std::vector<nc::Vector2> points = { { 0, -5 }, { 5, 5 }, { 0, 15 }, { -5, 5 }, { 0, -5 } };
nc::Color color{ 1, 1, 1 };
nc::Shape ship;
//nc::Shape shape { points, color };

nc::Transform transform{ { 400 , 300 }, 4, 0 };

float frametime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;



bool Update(float dt)
{
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	frametime = dt;
	roundTime += dt;
	if (roundTime >= 15)
	{
		gameOver = true;
	}

	if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) {
		dt = dt * 0.5f;
	}

	if (gameOver) dt = dt * 0.0f;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	//nc::Vector2 target = nc::Vector2{ x, y };
	//nc::Vector2 direction = target - position;
	//direction.Normalize();

	nc::Vector2 force;

	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * speed * dt; }
	nc::Vector2 direction = force;
	direction = nc::Vector2::Rotatate(direction, transform.angle);
	transform.position = transform.position + direction;

	if (Core::Input::IsPressed('A')) { transform.angle = transform.angle - dt * 5; }
	if (Core::Input::IsPressed('D')) { transform.angle = transform.angle + dt * 5; }



	//if (Core::Input::IsPressed('A')) position += nc::Vector2::left * speed * dt;
	//if (Core::Input::IsPressed('D')) position += nc::Vector2::right * speed * dt;
	//if (Core::Input::IsPressed('W')) position += nc::Vector2::up * speed * dt;
	//if (Core::Input::IsPressed('S')) position += nc::Vector2::down * speed * dt;

	//for (nc::Vector2& point : points) {
		//point = { nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
	//}

	return quit;
}

void Draw(Core::Graphics& graphics)
{

	ship.Draw(graphics, transform.position, transform.scale, transform.angle);

	if (gameOver) graphics.DrawString(400, 300, "game over");

	graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());

/*
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1 / frametime).c_str());

	graphics.SetColor(color.pack888());
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));

	for (size_t i = 0; i < points.size() - 1; i++)
	{
		//local / object space points
		nc::Vector2 p1 = points[i];
		nc::Vector2 p2 = points[i + 1];

		p1 = p1 * scale;
		p2 = p2 * scale;

		p1 = nc::Vector2::Rotatate(p1, angle);
		p2 = nc::Vector2::Rotatate(p2, angle);
		
		p1 = p1 + position;
		p2 = p2 + position;


		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
	*/


}

int main()
{
	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;
	//for (size_t i = 0; i < NUM_POINTS; i++) {
		//points.push_back(nc::Vector2{ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) });
	//}

	//ship.SetColor(nc::Color{ 1,1,1 });
	ship.load("shape.txt");

	prevTime = GetTickCount();

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}

