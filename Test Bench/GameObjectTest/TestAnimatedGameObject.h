#pragma once

#include "Framework.h"
#include "Components/RandomPosition.h"

void spawnAnimatedTestChar(entt::DefaultRegistry& registry, bloom::Game* gameInstance, const std::filesystem::path texturePath = "Assets/TestChar.png") {
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;
	using Sprite = bloom::components::Sprite;
	using AnimationPtr = bloom::components::AnimationPtr;
	using Animation = bloom::components::Animation;
	using AnimationSet = bloom::components::AnimationSet;

	auto thisEntity = registry.create();
	registry.assign<Position>(thisEntity, 50, 50);
	registry.assign<Size>(thisEntity, 256, 256);
	auto tmp = gameInstance->textures.load(texturePath);

	registry.assign<Sprite>(thisEntity, tmp, SDL_Rect{ 0,32,32,32 });


	// Seriously not the best way to initialize object animation.
	AnimationPtr down{ std::make_shared<Animation>() };
	down->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,32,32,32 }),
		Sprite(tmp, SDL_Rect{ 32,32,32,32 }),
		Sprite(tmp, SDL_Rect{ 0,32,32,32 }),
		Sprite(tmp, SDL_Rect{ 64,32,32,32 })
	};


	AnimationPtr up{ std::make_shared<Animation>() };
	up->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,0,32,32 }),
		Sprite(tmp, SDL_Rect{ 32,0,32,32 }),
		Sprite(tmp, SDL_Rect{ 0,0,32,32 }),
		Sprite(tmp, SDL_Rect{ 64,0,32,32 })
	};

	AnimationPtr left{ std::make_shared<Animation>() };
	left->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,64,32,32 }),
		Sprite(tmp, SDL_Rect{ 32,64,32,32 }),
		Sprite(tmp, SDL_Rect{ 0,64,32,32 }),
		Sprite(tmp, SDL_Rect{ 64,64,32,32 })
	};

	AnimationPtr right{ std::make_shared<Animation>() };
	right->animationFrames = {
		Sprite(tmp, SDL_Rect{ 0,96,32,32 }),
		Sprite(tmp, SDL_Rect{ 32,96,32,32 }),
		Sprite(tmp, SDL_Rect{ 0,96,32,32 }),
		Sprite(tmp, SDL_Rect{ 64,96,32,32 })
	};

	up->setFrameTime(250);
	down->setFrameTime(250);
	left->setFrameTime(250);
	right->setFrameTime(250);

	AnimationSet animSet;
	animSet.add("up", up);
	animSet.add("down", down);
	animSet.add("left", left);
	animSet.add("right", right);

	registry.assign<AnimationSet>(thisEntity, animSet);
	registry.assign<AnimationPtr>(thisEntity, up);
	registry.assign<RandomPosition>(thisEntity, RandomPosition{ 672,472 });
}