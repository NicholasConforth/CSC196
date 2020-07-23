#include "Game.h"
#include "Math/MathStuff.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/shape.h"
#include "Object/Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>

std::list<nc::Actor*> actors; //need to get rid of this


void Game::Startup()
{
	g_particleSystem.Startup();
	m_scene.Startup();
	m_scene.SetGame(this);
}

void Game::Shutdown()
{
	m_scene.Shutdown();
	g_particleSystem.Shutdown();
}

bool Game::Update(float dt)
{
	frametime = dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_state = eState::STARTGAME;
		}
		break;
	case Game::eState::STARTGAME:
	{
		Player* player = new Player;
		player->Load("Player.txt");
		m_scene.AddActor(player);
		for (int i = 0; i < 50; i++)
		{
			nc::Actor* enemy = new Enemy;
			enemy->Load("Enemy.txt");
			dynamic_cast<Enemy*>(enemy)->SetTarget(player);
			enemy->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
			dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 125));
			m_scene.AddActor(enemy);
		}
		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
		m_scene.Update(dt);
		spawntimer += dt;
		if (spawntimer >= 3.0f)
		{
			spawntimer = 0;

			Enemy* enemy = new Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<Player>());
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			m_scene.AddActor(enemy);
		}
		break;
	case Game::eState::GOMEOVER:
		break;
	default:
		break;
	}

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);
		nc::Color colors[] = { nc::Color::white, nc::Color::blue, nc::Color::yellow };
		nc::Color color = colors[rand() % 3];

		g_particleSystem.Create(nc::Vector2{ x, y }, 0, 180, 30, color, 1, 100, 200);

	}

	for (nc::Actor* actor : actors)
	{
		actor->Update(dt);
	}

	g_particleSystem.Update(dt);
	m_scene.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	for (nc::Actor* actor : actors)
	{
		actor->Draw(graphics);
	}

	
	g_particleSystem.Draw(graphics);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(250, 300, "SPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACE");
		break;
	case Game::eState::STARTGAME:
		break;
	case Game::eState::GAME:
		m_scene.Draw(graphics);
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(700, 40, std::to_string(m_score).c_str());
		break;
	case Game::eState::GOMEOVER:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(250, 300, "GAME OVER");
		break;
	default:
		break;
	}

	float v = (std::sin(t) + 1.0f);

	nc::Color c = nc::Lerp(nc::Color{ 0, 0, 1 }, nc::Color{ 1, 0, 0 }, v);
	graphics.SetColor(c);

	nc::Vector2 p = nc::Lerp(nc::Vector2{ 400, 300 }, nc::Vector2{ 400 , 100 }, v);
	graphics.DrawString(p.x, p.y, "Last Stawfightew");
}
