#pragma once
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif
#include <string>
#include <unordered_map>
using namespace std;

class ResourceManager {
public:
	static ResourceManager& GetInstance();

	SDL_Surface* GetSurface(string filePath);
private:
	ResourceManager();

	ResourceManager(ResourceManager const&);

	ResourceManager operator=(ResourceManager const&);

	~ResourceManager();

	// a string path(a picture) to a surface
	unordered_map<string, SDL_Surface*> m_surfaces;
};