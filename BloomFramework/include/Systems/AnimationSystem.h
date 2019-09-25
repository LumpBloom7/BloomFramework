#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"

namespace bloom::systems {
	void animationSystem(entt::DefaultRegistry& registry, double deltaTime = 0.0) {
		using AnimationPtr = bloom::components::AnimationPtr;
		using AnimationSet = bloom::components::AnimationSet;
		using Sprite = bloom::components::Sprite;

		registry.view<AnimationPtr>().each(
			[&](auto entity, AnimationPtr& anim) {
				if (registry.has<AnimationSet>(entity)) {
					AnimationPtr newAnim = registry.get<AnimationSet>(entity).getCurrent();
					if (newAnim)
						anim = newAnim;
				}
				registry.replace<Sprite>(entity, anim->update(deltaTime));
			}
		);
	}
}