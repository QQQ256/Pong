#include "SDLApp.hpp"

SDLApp::SDLApp(Uint32 subSystemFlags, const char* title, int x, int y, int w, int h) {

    m_width = w;
    m_height = h;
    m_maxFrameRate = 90;

    if (SDL_Init(subSystemFlags) < 0) {
        cout << "SDL could not be initialized: " <<
            SDL_GetError();
    }
    else {
        cout << "SDL video system is ready to go\n";
    }

    m_window = SDL_CreateWindow(
        title,
        x,
        y,
        w,
        h,
        SDL_WINDOW_SHOWN);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

void SDLApp::SetEventCallback(function<void(void)> func) {
    // 如何使用函数指针，直接用 = 进行指向即可
    m_EventCallback = func;
}

void SDLApp::SetRenderCallback(function<void(void)> func) {
    m_RenderCallback = func;
}

void SDLApp::SetUpdateCallback(function<void(void)> func) {
    m_UpdateCallback = func;
}

void SDLApp::RunLoop() {
    while (m_gameRunning) {
        Uint32 start = SDL_GetTicks();

        Uint32 buttons;
        buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
        // handle events first
        m_EventCallback();

        // then handle update
        m_UpdateCallback();

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);

        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // finally handle render
        m_RenderCallback();

        SDL_RenderPresent(m_renderer);

        Uint32 elapsedTime = SDL_GetTicks() - start;
        if (elapsedTime < m_maxFrameRate)
        {
            SDL_Delay(m_maxFrameRate - elapsedTime);
        }
    }
}

SDL_Renderer* SDLApp::GetRenderer() {
    return m_renderer;
}

SDLApp::~SDLApp() {

    SDL_DestroyWindow(m_window);

    SDL_Quit();
}

int SDLApp::GetMouseX() {
    return m_mouseX;
}

int SDLApp::GetMouseY() {
    return m_mouseY;
}

void SDLApp::StopAppLoop() {
    m_gameRunning = false;
}

void SDLApp::SetMaxFrameRate(int frameRate) {
    m_maxFrameRate = 1000 / frameRate;
}

int SDLApp::GetWindowWidth() {
    return m_width;
}

int SDLApp::GetWindowHeight() {
    return m_height;
}