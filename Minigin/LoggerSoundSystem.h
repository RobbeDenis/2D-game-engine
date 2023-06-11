#pragma once
#include "SoundSystemLocator.h"
#include <iostream>

namespace dae
{
	class LoggerSoundSystem final : public SoundSystem
	{
	public:
		LoggerSoundSystem(std::unique_ptr<SoundSystem> ss) 
			: _ss{ std::move(ss) } {};

		void Play(const sound_id id, const float volume) override
		{
			_ss->Play(id, volume);
			std::cout << "SSLogger: playing " << id << " at volume " << volume << "\n";
		}

		void RegisterSound(const sound_id id, const std::string& file) override
		{
			_ss->RegisterSound(id, file);
		}

		void Mute() override 
		{
			_ss->Mute();
		};

		void Unmute() override
		{
			_ss->Unmute();
		};

	private:
		std::unique_ptr<SoundSystem> _ss;

	};
}