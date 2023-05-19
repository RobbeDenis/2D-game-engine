#include "SDLSoundSystem.h"
#include "SDL_mixer.h"
#include <map>
#include <stdexcept>
#include <glm/common.hpp>
#include <thread>
#include <mutex>


class dae::SDLSoundSystem::SDLSoundSystemImpl
{
	static const unsigned int s_MaxPending = 16;

public:
	SDLSoundSystemImpl()
		: m_pSamples{ }
		, m_Path{ "../Data/Audio/" }
		, m_Head{ 0 }
		, m_Tail{ 0 }
		, m_Pending{ }
		, m_ExitFlag{ false }
		, m_QueueMutex{ }
		, m_ConditionVariable{ }
	{
		Mix_Init(0);

		int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 1, 512);
		if (result < 0)
			throw std::runtime_error{ "Could not open SDL Audio" };

		std::thread queueThread(&SDLSoundSystemImpl::PlayQueuedSounds, this);
		queueThread.detach();
	}

	~SDLSoundSystemImpl()
	{
		m_ExitFlag = true;
		m_ConditionVariable.notify_all();

		for (auto& sample : m_pSamples)
			Mix_FreeChunk(sample.second);

		Mix_CloseAudio();
		Mix_Quit();
	}

	void RegisterSound(const sound_id id, const std::string& file)
	{
		std::unique_lock<std::mutex> lock(m_QueueMutex);

		Mix_Chunk* sample;
		const std::string path = m_Path + file;
		sample = Mix_LoadWAV(path.c_str());

		if (!sample)
			throw std::runtime_error{ "SDLSoundSystem::RegisterSound Unable to load sound" };

		auto result = m_pSamples.insert(std::pair<sound_id, Mix_Chunk*>{id, sample});

		if (!result.second)
			throw std::runtime_error{ "SDLSoundSystem::RegisterSound " + file + " was already added"};

		lock.unlock();
		m_ConditionVariable.notify_all();
	}

#pragma warning(push, 0)
#pragma warning(disable:6385)
#pragma warning(disable:6386)
	void Play(const sound_id id, const float volume)
	{
		std::unique_lock<std::mutex> lock(m_QueueMutex);

		assert(((m_Tail + 1) % s_MaxPending) != m_Head);

		for (unsigned int i = m_Head; i != m_Tail; i = (i + 1) % s_MaxPending)
		{
			if (m_Pending[i].id == id)
			{
				m_Pending[i].volume = glm::max(volume, m_Pending[i].volume);
				return;
			}
		}

		m_Pending[m_Tail].id = id;
		m_Pending[m_Tail].volume = volume;
		m_Tail = (m_Tail + 1) % s_MaxPending;

		lock.unlock();
		m_ConditionVariable.notify_all();
	}
#pragma warning (pop)

	void PlayQueuedSounds()
	{
		while (!m_ExitFlag)
		{
			std::unique_lock<std::mutex> lock(m_QueueMutex);

			m_ConditionVariable.wait(lock, [this]() 
				{
					return m_Head != m_Tail || m_ExitFlag;
				});

			if (m_Head != m_Tail)
			{
				Mix_Chunk* const sample{ m_pSamples[m_Pending[m_Head].id] };

				float min = 0;
				float max = 128;
				float vol = m_Pending[m_Head].volume * max;
				vol = glm::clamp(vol, min, max);
				sample->volume = static_cast<Uint8>(vol);

				if (Mix_PlayChannel(-1, sample, 0) == -1)
					throw std::runtime_error{ SDL_GetError() };

				m_Head = (m_Head + 1) % s_MaxPending;
			}

			lock.unlock();
		}
	}

private:
	struct Sample
	{
		sound_id id;
		float volume;
	};

	Sample m_Pending[s_MaxPending];
	std::string m_Path;
	std::map<sound_id, Mix_Chunk*> m_pSamples;
	unsigned m_Head;
	unsigned m_Tail;
	
	std::atomic<bool> m_ExitFlag;
	std::condition_variable m_ConditionVariable;
	std::mutex m_QueueMutex;
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