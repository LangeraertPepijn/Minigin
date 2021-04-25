#pragma once
#include "SoundSystem.h"
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include "SDL_mixer.h"

namespace dae
{

	class SDLMixerSoundSystem : public SoundSystem
	{
	public:
		SDLMixerSoundSystem(bool isMuted);
		~SDLMixerSoundSystem();
		SDLMixerSoundSystem(const SDLMixerSoundSystem& other) = delete;
		SDLMixerSoundSystem(SDLMixerSoundSystem&& other) = delete;
		SDLMixerSoundSystem& operator=(const SDLMixerSoundSystem& other) = delete;
		SDLMixerSoundSystem& operator=(SDLMixerSoundSystem&& other) = delete;

		void AddSound(const std::string& sound);
		void Play(const SoundID id, const float volume) override;

		dae::SoundID GetNextFreeId() const;
	
	private:
		bool m_IsMuted{};
		
		std::mutex  m_SoundMutex;
		std::map<SoundID,std::string> m_Sounds;
		std::map<SoundID,Mix_Chunk*> m_SoundChunks;
		std::thread* m_pThread;
		std::queue<std::pair<dae::SoundID,const float>> m_PlayQueue;
		bool m_SoundIsRunning = true;
		void AddToQueue(dae::SoundID id,  const float volume);
		void ActivateThread();
		dae::SoundID m_NextFreeId;
	};
}
