#include "MiniginPCH.h"
#include "ServiceLocator.h"

NullSoundSystem ServiceLocator::m_NullSoundSystem;
SoundSystem* ServiceLocator::m_pSoundSystem = &m_NullSoundSystem;
void ServiceLocator::DeleteSoundSystem()
{
	if(m_pSoundSystem&& (m_pSoundSystem!=&m_NullSoundSystem))
	{
		delete m_pSoundSystem;
	}
}

ServiceLocator::~ServiceLocator()
{

}
