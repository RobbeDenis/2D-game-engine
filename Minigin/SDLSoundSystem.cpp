#include "SDLSoundSystem.h"
#include "SDL_mixer.h"
#include <map>
#include <stdexcept>
#include <glm/common.hpp>


class dae::SDLSoundSystem::SDLSoundSystemImpl
{
public:
	SDLSoundSystemImpl()
		: m_pSamples{ }
		, m_Path{ "../Data/Audio/" }
	{
		Mix_Init(0);

		int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 1, 512);
		if (result < 0)
			throw std::runtime_error{ "Could not open SDL Audio" };
	}

	~SDLSoundSystemImpl()
	{
		for (auto& sample : m_pSamples)
			Mix_FreeChunk(sample.second);

		Mix_CloseAudio();
		Mix_Quit();
	}

	void RegisterSound(const sound_id id, const std::string& file)
	{
		Mix_Chunk* sample;
		const std::string path = m_Path + file;
		sample = Mix_LoadWAV(path.c_str());

		if (!sample)
			throw std::runtime_error{ "SDLSoundSystem::RegisterSound Unable to load sound" };

		auto result = m_pSamples.insert(std::pair<sound_id, Mix_Chunk*>{id, sample});

		if (!result.second)
			throw std::runtime_error{ "SDLSoundSystem::RegisterSound " + file + " was already added"};
	}

	void Play(const sound_id id, const float volume)
	{
		Mix_Chunk* const sample{ m_pSamples[id]};

		float min = 0;
		float max = 128;
		float vol = volume * max;
		vol = glm::clamp(vol, min, max);

		sample->volume = static_cast<Uint8>(vol);

		if (Mix_PlayChannel(-1, sample, 0) == -1)
			throw std::runtime_error{ SDL_GetError() };
	}

private:
	std::string m_Path;
	std::map<sound_id, Mix_Chunk*> m_pSamples;
};

dae::SDLSoundSystem::SDLSoundSystem()
{
	m_pImpl = new SDLSoundSystemImpl();
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	delete m_pImpl;
}

void dae::SDLSoundSystem::Play(const sound_id id, const float volume)
{
	m_pImpl->Play(id, volume);
}

void dae::SDLSoundSystem::RegisterSound(const sound_id id, const std::string& file)
{
	m_pImpl->RegisterSound(id, file);
}