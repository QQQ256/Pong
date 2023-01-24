#include "TexturedRectangle.hpp"
#include "ResourceManager.hpp"

TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, string filePath) {

    SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filePath);
    m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);

    InitDefaults();
}

TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, string filePath, int r, int g, int b) {
    
    SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filePath);

    SDL_SetColorKey(retrieveSurface, SDL_TRUE, SDL_MapRGB(retrieveSurface->format, r, g, b));

    m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);

    InitDefaults();
    m_redColorKey = r;
    m_greenColorKey = g;
    m_blueColorKey = b;
}

void TexturedRectangle::InitDefaults() {
    m_rectangle.x = 0;
    m_rectangle.y = 0;
    m_rectangle.w = 32;
    m_rectangle.h = 32;

    m_redColorKey = 0xFF;
    m_greenColorKey = 0x00;
    m_blueColorKey = 0xFF;
}

TexturedRectangle::~TexturedRectangle() {
    SDL_DestroyTexture(m_texture);
}

void TexturedRectangle::SetPosition(int x, int y) {
    m_rectangle.x = x;
    m_rectangle.y = y;
}

void TexturedRectangle::SetDimention(int w, int h) {
    m_rectangle.w = w;
    m_rectangle.h = h;
}

void TexturedRectangle::Update() {

}

void TexturedRectangle::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}

int TexturedRectangle::GetPositionX() {
    return m_rectangle.x;
}

int TexturedRectangle::GetPositionY() {
    return m_rectangle.y;
}

int TexturedRectangle::GetWidth() {
    return m_rectangle.w;
}

int TexturedRectangle::GetHeight() {
    return m_rectangle.h;
}

