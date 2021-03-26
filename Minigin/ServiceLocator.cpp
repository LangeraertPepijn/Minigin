#include "MiniginPCH.h"
#include "ServiceLocator.h"

dae::NullSoundSystem dae::ServiceLocator::m_NullSoundSystem;
dae::SoundSystem* dae::ServiceLocator::m_pSoundSystem = &m_NullSoundSystem;
void dae::ServiceLocator::DeleteSoundSystem()
{
	if(m_pSoundSystem&& (m_pSoundSystem!=&m_NullSoundSystem))
	{
		delete m_pSoundSystem;
	}
}

dae::ServiceLocator::~ServiceLocator()
{

}
