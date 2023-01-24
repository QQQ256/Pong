#pragma once
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif
#include <string>
using namespace std;

class TexturedRectangle {
public:

    TexturedRectangle(SDL_Renderer* renderer, string filePath);
    TexturedRectangle(SDL_Renderer* renderer, string filePath, int r, int g, int b);

    void InitDefaults();

    ~TexturedRectangle();

    void SetPosition(int x, int y);

    void SetDimention(int w, int h);

    int GetPositionX();

    int GetPositionY();

    int GetWidth();

    int GetHeight();

    void Update();

    void Render(SDL_Renderer* renderer);

private:

    inline const SDL_Rect GetRectangle(){ return m_rectangle; }

    SDL_Rect        m_rectangle;
    SDL_Texture*    m_texture;

    int             m_redColorKey;
    int             m_greenColorKey;
    int             m_blueColorKey;
};