#pragma once
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif
#include <iostream>
#include <functional>
using namespace std;

class SDLApp {
public:
    SDLApp(Uint32 subSystemFlags, const char* title, int x, int y, int w, int h);

    ~SDLApp();

    void SetEventCallback(function<void(void)> func);

    void SetRenderCallback(function<void(void)> func);

    void SetUpdateCallback(function<void(void)> func);

    void RunLoop();

    SDL_Renderer* GetRenderer();

    int GetMouseX();

    int GetMouseY();
    // stop running app
    void StopAppLoop();
    // set max frame frameRate = the frame you want to set
    void SetMaxFrameRate(int frameRate);

    int GetWindowWidth();

    int GetWindowHeight();

private:
    SDL_Window*                 m_window = nullptr;
    SDL_Renderer*               m_renderer = nullptr;
    bool                        m_gameRunning = true;

    // get mouse pos
    int                         m_mouseX;
    int                         m_mouseY;

    int                         m_maxFrameRate;
    int                         m_width;
    int                         m_height;
    
    // function pointer, which points to a function
    std::function<void(void)>   m_EventCallback;
    std::function<void(void)>   m_RenderCallback;
    std::function<void(void)>   m_UpdateCallback;

};