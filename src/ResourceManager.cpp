#include "ResourceManager.hpp"

// Instantiate exactly 1 instance of the class here
// singleton mode
ResourceManager& ResourceManager::GetInstance() {
	static ResourceManager* s_instance = new ResourceManager;

	return *s_instance;
}

ResourceManager::ResourceManager() {

}

ResourceManager::ResourceManager(ResourceManager const&) {

}

// maybe useless 
ResourceManager ResourceManager::operator=(ResourceManager const&) {
	return *this;
}

ResourceManager::~ResourceManager() {

}

/// <summary>
/// get surface based on path, if not exist, add to the map
/// </summary>
/// <param name="filePath"></param>
/// <returns></returns>
SDL_Surface* ResourceManager::GetSurface(string filePath) {

	auto search = m_surfaces.find(filePath);
	if (search != m_surfaces.end())
	{
		return m_surfaces[filePath];
	}
	else {
		SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
		m_surfaces.insert(make_pair(filePath, surface));

		return m_surfaces[filePath];
	}

	return nullptr;
}