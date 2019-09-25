#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"

namespace bloom::systems {
	void renderSystem(entt::DefaultRegistry& registry, double deltaTime = 0.0) {
		using Position = bloom::components::Position;
		using Size = bloom::components::Size;
		using Sprite = bloom::components::Sprite;

		registry.view<Position, Size, Sprite>().each(
			[](auto entity, Position& pos, Size& size, Sprite& spr) {
				SDL_Rect destRect{
					static_cast<int>(pos.x),
					static_cast<int>(pos.y),
					static_cast<int>(size.w),
					static_cast<int>(size.h)
				};
				spr.texture->render(spr.srcRect, destRect);
			}
		);
	}
}