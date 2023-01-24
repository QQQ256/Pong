#include "GameEntity.hpp"
#include "Collider2D.hpp"

GameEntity::GameEntity() {
	m_sprite = nullptr;
	m_renderer = nullptr;
}

GameEntity::GameEntity(SDL_Renderer* renderer) {
	m_sprite = nullptr;
	m_renderer = renderer;
}

void GameEntity::AddTexturedRectangleComponent(string spritePath) {
	m_sprite = new TexturedRectangle(m_renderer, spritePath);
}

void GameEntity::AddTexturedRectangleComponent(string spritePath, int r, int g, int b) {
	m_sprite = new TexturedRectangle(m_renderer, spritePath, r, g, b);
}

void GameEntity::AddBoxBoxCollider2D() {
	m_colliders.push_back(new BoxCollider2D());
}

//GameEntity::GameEntity(SDL_Renderer* renderer, string spritePath) {
//	m_Renderer = renderer;
//	m_sprite = new TexturedRectangle(m_Renderer, spritePath);
//	m_collider = new BoxCollider2D();
//}

GameEntity::~GameEntity() {
	if (m_sprite != nullptr)
	{
		delete m_sprite;
	}
	
	for (int i = 0; i < m_colliders.size(); i++)
	{
		delete m_colliders[i];
	}
}

void GameEntity::Update() {
}

void GameEntity::Render() {
	if (m_sprite != nullptr)
	{
		m_sprite->Render(m_renderer);
	}

	// for (int i = 0; i < m_colliders.size(); i++)
	// {
	// 	if (m_colliders[i] != nullptr)
	// 	{
	// 		// add color for the collider
	// 		SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);

	// 		SDL_RenderDrawRect(m_renderer, &m_colliders[i]->GetColliderBoundingBox());
	// 	}
	// }
}

TexturedRectangle& GameEntity::GetTexturedRectangle() {
	return *m_sprite;
}

BoxCollider2D& GameEntity::GetBoxCollider2D(int index) {
	return *m_colliders[index];
}

void GameEntity::SetPosition(int x, int y) {
	if (m_sprite != nullptr)
	{
		m_sprite->SetPosition(x, y);
	}

	for (int i = 0; i < m_colliders.size(); i++)
	{
		if (m_colliders[i] != nullptr)
		{
			m_colliders[i]->SetAbsolutePosition(x, y);
		}
	}
}

void GameEntity::SetDimention(int w, int h) {
	if (m_sprite != nullptr)
	{
		m_sprite->SetDimention(w, h);
	}

	for (int i = 0; i < m_colliders.size(); i++)
	{
		if (m_colliders[i] != nullptr)
		{
			m_colliders[i]->SetDimention(w, h);
		}
	}
}