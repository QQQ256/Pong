#pragma once
#include <string>
// #include <SDL_ttf.h>
// #if defined(LINUX) || defined(MINGW)
// 	#include <SDL2/SDL.h>
//     #include <SDL2/SDL_ttf.h>
// #else
// 	// Windows and Mac use a different path
// 	// If you have compilation errors, change this as needed.
// 	#include <SDL.h>
// #endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class DynamicText {
public:

    DynamicText(std::string fontfilepath, size_t fontSize);

    ~DynamicText();

    void DrawText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h);

private:

    SDL_Rect m_rectangle;
    SDL_Texture* m_texture;
    SDL_Surface* m_surface;

    TTF_Font* m_ourFont;

    static bool s_ttfInitialized;

};