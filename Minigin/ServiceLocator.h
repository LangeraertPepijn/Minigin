#pragma once
#include "SoundSystem.h"
#include "NullSoundSystem.h"



class ServiceLocator final

{
private:
	static SoundSystem* m_pSoundSystem;
	static NullSoundSystem m_NullSoundSystem;

public:
	static void DeleteSoundSystem();
	~ServiceLocator();
	ServiceLocator(const ServiceLocator& other) = delete;
	ServiceLocator(ServiceLocator&& other) = delete;
	ServiceLocator& operator=(const ServiceLocator& other) = delete;
	ServiceLocator& operator=(ServiceLocator&& other) = delete;

	static SoundSystem* GetSoundSystem() { return m_pSoundSystem; };

	static void RegisterSoundSystem(SoundSystem* soundSystem)
	{
		DeleteSoundSystem();
		if (soundSystem == nullptr)
		{
			m_pSoundSystem = &m_NullSoundSystem;
		}
		else
		{
			m_pSoundSystem = soundSystem;
		}

	}
};



