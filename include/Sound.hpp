#pragma once
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif
#include <string>

class ISound {
public:
	virtual ~ISound() {};
	virtual void PlaySound() = 0;
	virtual void StopSound() = 0;
};

class Sound : public ISound {
public:
	Sound(std::string path);

	~Sound();

	void PlaySound();

	void StopSound();

	void SetupDevice();

private:
	SDL_AudioDeviceID	m_device;

	SDL_AudioSpec		m_audioSpec;
	Uint8*				m_waveStart;
	Uint32				m_waveLength;
};