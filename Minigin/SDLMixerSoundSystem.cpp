#include "MiniginPCH.h"
#include "SDLMixerSoundSystem.h"


dae::SDLMixerSoundSystem::SDLMixerSoundSystem(bool isMuted)
	: m_IsMuted(isMuted)

{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	ActivateThread();
}

dae::SDLMixerSoundSystem::~SDLMixerSoundSystem()
{
	m_SoundIsRunning = false;
	if(m_pThread->joinable())
	{
		m_pThread->join();
	}
	if (m_pThread)
	{
		delete m_pThread;
		m_pThread = nullptr;
	}
	for(auto i = m_SoundChunks.begin();i!=m_SoundChunks.end();i++)
	{
		Mix_FreeChunk(i->second);
	}
	Mix_CloseAudio();
}

void dae::SDLMixerSoundSystem::AddSound(SoundID id, const std::string& sound)
{
	m_Sounds[id]=sound;
	std::lock_guard<std::mutex> guard{ m_SoundMutex };
	m_SoundChunks[id] = Mix_LoadWAV(m_Sounds[id].c_str());

}

void dae::SDLMixerSoundSystem::Play(const SoundID id, const float volume)
{
	AddToQueue(id, volume);
}

void dae::SDLMixerSoundSystem::ActivateThread()
{

	if (m_pThread == nullptr)
	{
		m_pThread = new std::thread([this]()
			{
				while (this->m_SoundIsRunning)
				{
					std::lock_guard<std::mutex> guard{ m_SoundMutex };
					while (0 != m_PlayQueue.size())
					{
						auto settings = m_PlayQueue.back();
						float temp = settings.second;
						m_SoundChunks[settings.first]->volume = static_cast<UINT8>(temp);
						Mix_PlayChannel(-1, m_SoundChunks[settings.first], 0);
						m_PlayQueue.pop();
					}
				}
			});
	}
}

void dae::SDLMixerSoundSystem::AddToQueue(dae::SoundID id, const float volume)
{
	std::lock_guard<std::mutex> guard{ m_SoundMutex };
	m_PlayQueue.push(std::pair<dae::SoundID,const float>(id,volume));
}




