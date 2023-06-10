#include "Game.h"
#include "SceneManager.h"

pacman::Game::Game()
{
}

void pacman::Game::SetScene(unsigned id)
{
	auto& sm{ dae::SceneManager::GetInstance() };
	sm.SetScene(id);
}
