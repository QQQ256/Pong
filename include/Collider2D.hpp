#pragma once
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif
#include "Vector2D.hpp"

class ICollider2D {
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
};

class BoxCollider2D : public ICollider2D {
public:
	BoxCollider2D();

	~BoxCollider2D();

	SDL_Rect& GetColliderBoundingBox();

	SDL_bool IsColliding(BoxCollider2D& collider);

	void SetAbsolutePosition(int x, int y);

	void SetDimention(int w, int h);

	void Update();

	void Render();

	// ����ÿ��ͼƬ�ĸ������һ�����ֵĵ����ص㣬������С����
	// �÷���Ϊ��sprite��collider
	Vector2D SetBoundingBoxAutomatically(SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b);
private:
	// �Ż�������Ϊָ�룬�ɶ����Ƿ���ڽ����ж�
	SDL_Rect* m_colliderRectangle;
};