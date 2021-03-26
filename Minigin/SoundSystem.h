#pragma once

namespace dae
{
	using SoundID = unsigned short;

	class SoundSystem
	{
	public:
		SoundSystem();
		virtual ~SoundSystem() = default;

		virtual void Play(const SoundID id, const float volume) = 0;
	private:

	};

}