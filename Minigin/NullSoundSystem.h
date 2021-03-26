#pragma once
#include  "SoundSystem.h"

namespace dae
{

	class NullSoundSystem final :public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		virtual~NullSoundSystem() = default;
		NullSoundSystem(const NullSoundSystem& other) = delete;
		NullSoundSystem(NullSoundSystem&& other) = delete;
		NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
		NullSoundSystem& operator=(NullSoundSystem&& other) = delete;
		void Play(const SoundID, const float) override {};
	private:

	};

}