#pragma once
#include "SoundSystemLocator.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();

		void Play(const sound_id id, const float volume) override;
		void RegisterSound(const sound_id id, const std::string& file) override;
		void Mute() override;
		void Unmute() override;

	private:
		class SDLSoundSystemImpl;
		SDLSoundSystemImpl* m_pImpl;
	};
}

