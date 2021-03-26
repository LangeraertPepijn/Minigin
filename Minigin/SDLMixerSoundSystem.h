#pragma once
#include "SoundSystem.h"
#include <map>
#include <mutex>
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

		void AddSound(SoundID id,const std::string& sound);
		void Play(const SoundID id, const float volume) override;
	private:
		bool m_IsMuted{};
		
		std::mutex  m_SoundMutex;
		std::map<SoundID,std::string> m_Sounds;
	};
}
