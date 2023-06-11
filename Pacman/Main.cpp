#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>
#include <InputManager.h>
#include <SoundSystemLocator.h>
#include <LoggerSoundSystem.h>
#include <SDLSoundSystem.h>

#include "CreateScenes.h"
#include "PacmanSounds.h"

void load();

int main(int, char* []) 
{
	dae::Minigin engine{ "../Data/", 640, 540 };
	engine.Run(load);
	return 0;
}

void load()
{
	auto& input = dae::InputManager::GetInstance();

	input.AddXBoxController(0);
	input.AddXBoxController(1);

#if _DEBUG
	dae::SoundSystemLocator::RegisterSoundSystem(std::make_unique<dae::LoggerSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
#else
	dae::SoundSystemLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
#endif

	auto& ss{ dae::SoundSystemLocator::GetSoundSystem() };
	ss.RegisterSound(PacmanSounds::Chomp, "pacman_chomp.wav");
	ss.RegisterSound(PacmanSounds::EatFruit, "pacman_eatfruit.wav");
	ss.RegisterSound(PacmanSounds::EatGhost, "pacman_eatghost.wav");
	ss.RegisterSound(PacmanSounds::PacmanDeath, "pacman_death.wav");
	ss.RegisterSound(PacmanSounds::EatPower, "pacman_power.wav");
	ss.RegisterSound(PacmanSounds::GameStart, "game_start.wav");
	ss.RegisterSound(PacmanSounds::Press, "credit.wav");
	ss.RegisterSound(PacmanSounds::Click1, "cick-001.wav");
	ss.RegisterSound(PacmanSounds::Click2, "cick-002.wav");

	CreateMainMenu();
	CreateSinglePlayer();
	CreateCoop();
	CreateVersus();
	CreateInsertName();
	CreateLeaderboard();
}