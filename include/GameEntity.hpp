#pragma once
#include "TexturedRectangle.hpp"
#include "Collider2D.hpp"
#include <vector>

class GameEntity {
public:
	GameEntity();

	GameEntity(SDL_Renderer* renderer);

	~GameEntity();
	// Updated, called every loop
	void Update();
	// Render game entity
	void Render();

	void AddTexturedRectangleComponent(string spritePath);

	void AddTexturedRectangleComponent(string spritePath, int r, int g, int b);

	void AddBoxBoxCollider2D();

	TexturedRectangle& GetTexturedRectangle();

	BoxCollider2D& GetBoxCollider2D(int index);

	// Set the position of the object and move all body components to this position
	// This is done to simplify the process of setting the position after joining the collider
	// Now there are only two components on the entity: sprite and collider, one-time setting in this function
	void SetPosition(int x, int y);

	void SetDimention(int w, int h);
private:
	TexturedRectangle*		m_sprite;
	SDL_Renderer*			m_renderer;
	vector<BoxCollider2D*>		m_colliders; // to set more colliders in an object, use a vector
};