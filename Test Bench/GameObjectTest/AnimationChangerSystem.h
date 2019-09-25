#pragma once

#include "Framework.h"

/*
 Crap system just to test if shit works, don't mind the hard coded fuckery here.
 Definitely shouldn't be in bloom::systems.
*/
void animationChangerSystem(entt::DefaultRegistry& registry, double deltaTime = 0.0) {
	using AnimationSet = bloom::components::AnimationSet;
	using AnimationPtr = bloom::components::AnimationPtr;

	static int counter = 99;
	const std::vector<std::string> animations{
		"up",
		"down",
		"left",
		"right"
	};
	counter = (counter + 1) % 100;
	if (counter == 0) {
		registry.view<AnimationSet>().each(
			[&](auto entity, AnimationSet& animSet) {
				animSet.changeCurrent(animations[rand() % 4]);
			}
		);
	}
}