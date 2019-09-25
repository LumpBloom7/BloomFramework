#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

void spawnTestChar(
	entt::DefaultRegistry& registry,
	bloom::Game* gameInstance,
	SDL_Rect pos_and_size = SDL_Rect{ 50,50, 256, 256 },
	const std::filesystem::path texturePath = "Assets/TestChar.png",
	std::optional<SDL_Rect> srcRect = std::nullopt, bool random = false)
{
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;
	using Sprite = bloom::components::Sprite;

	auto thisEntity = registry.create();
	registry.assign<Position>(thisEntity, pos_and_size.x, pos_and_size.y);
	registry.assign<Size>(thisEntity, pos_and_size.w, pos_and_size.h);
	registry.assign<Sprite>(thisEntity, gameInstance->textures.load(texturePath), srcRect);

	if (random)
		registry.assign<RandomPosition>(thisEntity, RandomPosition{ 672,472 });
}