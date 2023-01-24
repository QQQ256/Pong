#include "Collider2D.hpp"
#include <iostream>
using namespace std;

BoxCollider2D::BoxCollider2D() {
	m_colliderRectangle = new SDL_Rect;
	m_colliderRectangle->x = 0;
	m_colliderRectangle->y = 0;
	m_colliderRectangle->w = 0;
	m_colliderRectangle->h = 0;
}

BoxCollider2D::~BoxCollider2D() {

}

SDL_Rect& BoxCollider2D::GetColliderBoundingBox() {
	return *m_colliderRectangle;
}

SDL_bool BoxCollider2D::IsColliding(BoxCollider2D& collider) {

	if (m_colliderRectangle == nullptr)
	{
		return SDL_FALSE;
	}
	
	const SDL_Rect* temp = collider.m_colliderRectangle; 
	if (temp == nullptr)
	{
		return SDL_FALSE;
	}

	return SDL_HasIntersection(m_colliderRectangle, temp);
}

void BoxCollider2D::SetAbsolutePosition(int x, int y) {
	m_colliderRectangle->x = x;
	m_colliderRectangle->y = y;
}

void BoxCollider2D::SetDimention(int w, int h) {
	m_colliderRectangle->w = w;
	m_colliderRectangle->h = h;
}

void BoxCollider2D::Update() {
	// ??????????
}

void BoxCollider2D::Render() {

}

Vector2D BoxCollider2D::SetBoundingBoxAutomatically(SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b) {

	// ?????surface???????????
	if (surface == nullptr)
	{
		cout << "SetBoundingBoxAutomatically is failed, no surface is found here." << endl;
	}

	SDL_LockSurface(surface);
	int w = surface->w;
	int h = surface->h;
	// pitch -> Length of a surface scanline in bytes
	int pitch = surface->pitch;
	// 1 pitch = 1 colorChannel = RGB/RGBA
	int colorChannels = pitch / w;

	//cout << "colorChannels: " << colorChannels << endl;

	Uint8* pixels = (Uint8*)surface->pixels;

	SDL_UnlockSurface(surface);

	int xMin = w;
	int xMax = 0;
	int yMin = h;
	int yMax = 0;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w * colorChannels; x += colorChannels)
		{
			// y * (w * colorChannels) -> move to the line where the pixel is located
			// + 0 = b/r, + 1 = g/g, +2 = r/b
			if (!(pixels[y * (w * colorChannels) + x + 0] == b &&
				pixels[y * (w * colorChannels) + x + 1] == g &&
				pixels[y * (w * colorChannels) + x + 2] == r))
			{
				xMin = min(x, xMin);
				yMin = min(y, yMin);
				xMax = max(x, xMax);
				yMax = max(y, yMax);
				
			}
		}
	}

	int scale = (1200 / 300);
	m_colliderRectangle->w = (xMax / colorChannels - xMin / colorChannels) / (scale);
	m_colliderRectangle->h = (yMax  - yMin) / (scale);

	//cout << "m_colliderRectangle->w: " << m_colliderRectangle->w << endl;
	//cout << "m_colliderRectangle->h: " << m_colliderRectangle->h << endl;

	Vector2D result;
	result.x = xMin / (colorChannels * scale);
	result.y = yMin / scale;

	return result;
}