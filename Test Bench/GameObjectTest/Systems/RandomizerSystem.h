#pragma once

#include "Framework.h"
#include "../Components/RandomPosition.h"

void positionRandomizerSystem(entt::DefaultRegistry& registry, double deltaTime = 0.0) {
	using Position = bloom::components::Position;
	registry.view<Position, RandomPosition>().each(
		[](auto entity, Position& pos, RandomPosition& randPos) {
			pos.x = rand() % randPos.maxX;
			pos.y = rand() % randPos.maxY;
		}
	);
};