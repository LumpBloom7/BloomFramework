#pragma once

#include "Framework.h"

class TestMovableObject : public bloom::GameObject {
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;
	using Sprite = bloom::components::Sprite;
	using bloom::GameObject::GameObject;

public:
	void init() override {}

	void init(SDL_Rect pos_and_size = SDL_Rect{ 0,0, 50, 50 }, const std::filesystem::path texturePath = "Assets/Box.png", std::optional<SDL_Rect> srcRect = std::nullopt) {
		pos = &m_registry.replace<Position>(m_entity, pos_and_size.x, pos_and_size.y);
		m_registry.replace<Size>(m_entity, pos_and_size.w, pos_and_size.h);
		auto tmp = c_gameInstance->textures.load(texturePath);
		m_registry.assign<Sprite>(m_entity, tmp, srcRect);
	}

	void updatePos(int xOffset, int yOffset) {
		pos->x += xOffset;
		pos->y += yOffset;
	}

private:
	Position* pos;
};