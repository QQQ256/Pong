#include "Sound.hpp"
#include <iostream>

Sound::Sound(std::string path) {
	if (SDL_LoadWAV(path.c_str(), &m_audioSpec, &m_waveStart, &m_waveLength) == nullptr)
	{
		std::cout << " Sound loading error: " << SDL_GetError() << std::endl;
	}
}

Sound::~Sound() {
	SDL_FreeWAV(m_waveStart);
	SDL_CloseAudioDevice(m_device);
}

void Sound::PlaySound() {
	int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLength);
	SDL_PauseAudioDevice(m_device, 0);
}

void Sound::StopSound() {
	SDL_PauseAudioDevice(m_device, 1);
}

void Sound::SetupDevice() {
	m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, 0);
	
	// if no audio can play here, output SDL_ERROR()
	if (0 == m_device) {
		std::cerr << "sound device error: " << SDL_GetError() << std::endl;
	}
}