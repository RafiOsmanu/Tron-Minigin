#include "AudioNavigator.h"

#include <SDL_mixer.h>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <map>


class Engine::Sdl_AudioNavigator::Sdl_AudioNavigatorImpl final
{
public:
	Sdl_AudioNavigatorImpl()
	{
		InitMixer();
	}

	~Sdl_AudioNavigatorImpl()
	{
		CloseMixer();
	}

	void InitMixer()
	{
		Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

		m_Thread = std::jthread(&Sdl_AudioNavigatorImpl::Update, this);

		m_IsMixerClosed = false;
	}

	void CloseMixer()
	{
		if (m_IsMixerClosed) return;

		m_IsMixerClosed = true;

		for (auto& sound : m_Sounds)
		{
			if (sound.second.isLoaded)
			{
				Mix_FreeChunk(sound.second.pChunk);
				sound.second.isLoaded = false;
			}
		}

		Mix_CloseAudio();
		Mix_Quit();

		//notify the thread to stop
		m_ConditionVariable.notify_all();
	}

	void PlaySound(const SoundId id, const float volume)
	{
		if(m_IsMixerClosed) return;

		std::lock_guard<std::mutex> lock(m_CvMutex);
		SoundRequest request{};
		request.id = id;
		request.volume = volume;

		m_SoundRequests.push(request);

		//notify the thread to play the sound
		m_ConditionVariable.notify_all();
	}

	void MuteAllAudio()
	{
		if (!m_IsAudioMuted)
		{
			m_IsAudioMuted = true;
			Mix_MasterVolume(0);
		}
		else
		{
			m_IsAudioMuted = false;
			Mix_MasterVolume(MIX_MAX_VOLUME);
		}
	}

	void StopSound(const SoundId id)
	{
		if (m_IsMixerClosed) return;
		Mix_HaltChannel(id);
		
	}
	void AddSound(const std::string& path, const SoundId id, bool loopSound = false)
	{
		if (m_IsMixerClosed) return;
		Sound sound;
		sound.path = "../Data/Sounds/" + path;
		sound.pChunk = nullptr;
		sound.isLoaded = false;
		sound.loopSound = loopSound;
		m_Sounds.emplace(id, sound);
	}

	bool GetMixerClosed()
	{
		return m_IsMixerClosed; 
	}




private:

	struct Sound
	{
		std::string path;
		Mix_Chunk* pChunk{};
		bool isLoaded{};
		bool loopSound{};
	};

	struct SoundRequest
	{
		SoundId id{};
		float volume{};
	};

	std::map<SoundId, Sound> m_Sounds;
	std::queue<SoundRequest> m_SoundRequests;

	std::condition_variable m_ConditionVariable;
	std::mutex m_CvMutex;

	std::jthread m_Thread;
	bool m_IsMixerClosed{ true };

	bool m_IsAudioMuted{ false };

	void Update()
	{
		while (true)
		{

			//wait until the queue is not empty
			std::unique_lock<std::mutex> lock(m_CvMutex);
			m_ConditionVariable.wait(lock, [&] {return !m_SoundRequests.empty() || m_IsMixerClosed; });


			if (m_IsMixerClosed)
				return;

			
			const SoundRequest& request = m_SoundRequests.front();
			m_SoundRequests.pop();

			//release the lock before playing the sound
			lock.unlock();

			// Requested sound is not in the list of sounds
			if (request.id >= m_Sounds.size()) continue;
			

			auto& sound = m_Sounds[request.id];

			if (!sound.isLoaded)
			{
				sound.pChunk = Mix_LoadWAV(sound.path.c_str());
				sound.isLoaded = true;
			}

			// Play the sound
			Mix_VolumeChunk(sound.pChunk, static_cast<int>(request.volume));
			if(sound.loopSound)
				Mix_PlayChannel(request.id, sound.pChunk, -1);
			else
				Mix_PlayChannel(request.id, sound.pChunk, 0);
		}
	}
};

Engine::Sdl_AudioNavigator::Sdl_AudioNavigator()
{
	m_pImpl = std::make_unique<Sdl_AudioNavigatorImpl>();
}

void Engine::Sdl_AudioNavigator::Play(const SoundId id, const float volume)
{
	m_pImpl->PlaySound(id, volume);
}

void Engine::Sdl_AudioNavigator::Stop(const SoundId id)
{
	m_pImpl->StopSound(id);
}

void Engine::Sdl_AudioNavigator::MuteAllAudio()
{
	m_pImpl->MuteAllAudio();
}

void Engine::Sdl_AudioNavigator::AddSound(const std::string& path, const SoundId id, bool loopSound)
{
	m_pImpl->AddSound(path, id, loopSound);
}

void Engine::Sdl_AudioNavigator::InitMixer()
{
	m_pImpl->InitMixer();
}

void Engine::Sdl_AudioNavigator::CloseMixer()
{
	m_pImpl->CloseMixer();
}

bool Engine::Sdl_AudioNavigator::IsMixerClosed()
{
	return m_pImpl->GetMixerClosed();
}
