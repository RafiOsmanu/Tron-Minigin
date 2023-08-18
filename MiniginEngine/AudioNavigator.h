#pragma once
#include <string>
#include <memory>
namespace Engine
{
	using SoundId = unsigned short;

	enum class Sound : unsigned short
	{
		mainMenu,
		background,
		loseGame,
		shoot,
		teleport
	};

	class BaseAudioNavigator
	{
	public:
		virtual ~BaseAudioNavigator() = default;
		virtual void Play(const SoundId id, const float volume) = 0;
		virtual void Stop(const SoundId id) = 0;
		virtual void MuteAllAudio() = 0;
		virtual void AddSound(const std::string& path, const SoundId id, bool loopSound = false) = 0;

		virtual void InitMixer() = 0;
		virtual void CloseMixer() = 0;
		virtual bool IsMixerClosed() = 0;
	};

	class AudioNavigatorNull final : public BaseAudioNavigator
	{
	public:
		virtual void Play(const SoundId , const float ) {};
		virtual void Stop(const SoundId ) {};
		virtual void MuteAllAudio() {};
		virtual void AddSound(const std::string& , const SoundId , bool  = false) {};

		virtual void InitMixer() {};
		virtual void CloseMixer() {};
		virtual bool IsMixerClosed() { return false; }
	};

	class Sdl_AudioNavigator final : public BaseAudioNavigator
	{
	public:
		Sdl_AudioNavigator();
		virtual ~Sdl_AudioNavigator() = default;

		virtual void Play(const SoundId id, const float volume) override;
		virtual void Stop(const SoundId id) override;
		virtual void MuteAllAudio() override;
		virtual void AddSound(const std::string& path, const SoundId id, bool loopSound = false) override;

		virtual void InitMixer() override;
		virtual void CloseMixer() override;
		virtual bool IsMixerClosed() override;

	private :
		class Sdl_AudioNavigatorImpl;
		std::unique_ptr<Sdl_AudioNavigatorImpl> m_pImpl;
	};
}

