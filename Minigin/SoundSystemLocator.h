#pragma once
#include <memory>
#include <string>

namespace dae
{
	using sound_id = unsigned int;

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const sound_id id, const float volume) = 0;
		virtual void Mute() = 0;
		virtual void Unmute() = 0;
		virtual void RegisterSound(const sound_id id, const std::string& file) = 0;
	};

	class null_SoundSystem final : public SoundSystem
	{
		void Play(const sound_id, const float) override {};
		void RegisterSound(const sound_id, const std::string&) override {};
		void Mute() override {};
		void Unmute() override {};
	};

	class SoundSystemLocator final
	{
	private:
		static std::unique_ptr<SoundSystem> _ss_instance;

	public:
		static SoundSystem& GetSoundSystem() { return *_ss_instance; };
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem> ss)
		{
			if (ss == nullptr)
				_ss_instance = std::make_unique<null_SoundSystem>();
			else
				_ss_instance = std::move(ss);
		};
	};
}