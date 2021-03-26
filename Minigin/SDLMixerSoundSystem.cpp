#include "MiniginPCH.h"
#include "SDLMixerSoundSystem.h"
#include "SDL_mixer.h"

dae::SDLMixerSoundSystem::SDLMixerSoundSystem(bool isMuted)
	: m_IsMuted(isMuted)

{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
}

dae::SDLMixerSoundSystem::~SDLMixerSoundSystem()
{
	Mix_CloseAudio();
}

void dae::SDLMixerSoundSystem::AddSound(SoundID id, const std::string& sound)
{
	std::lock_guard<std::mutex> guard{ m_SoundMutex };
	 m_Sounds[id]=sound;
}

void dae::SDLMixerSoundSystem::Play(const SoundID id, const float volume)
{
	Mix_Chunk* song = Mix_LoadWAV(m_Sounds[id].c_str());
	float temp = volume;
	song->volume = static_cast<UINT8>(temp);
	Mix_PlayChannel(-1, song, 0);
}
