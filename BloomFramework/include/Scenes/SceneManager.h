#pragma once

#include "stdIncludes.h"
#include "Scene.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Game;

	class BLOOMFRAMEWORK_API SceneManager {
		friend Scene::Scene(SceneManager & sceneManager);

	public:
		SceneManager(Game& gameInstance);

		template<class Scn, typename InitFunc, typename... TArgs>
		void changeScene(std::shared_ptr<Scn> newScene, InitFunc init, TArgs &&... initArgs);

		template<class Scn>
		void changeScene(std::shared_ptr<Scn> newScene);

		void update(double deltaTime);
		void draw();

	private:
		std::shared_ptr<Scene> m_currScene;
		Game & m_gameInstance;
	};

	template<class Scn, typename InitFunc, typename... TArgs>
	void SceneManager::changeScene(std::shared_ptr<Scn> newScene, InitFunc init, TArgs &&... initArgs) {
		static_assert(std::is_base_of_v<Scene, Scn>, "Type Scn passed in is not Scene based");

		m_currScene = newScene;
		
		if (m_currScene->loadThis){
			if constexpr (std::is_member_function_pointer_v<InitFunc>)
				(*newScene.*init)(std::forward<TArgs>(initArgs)...);
			else
				init(newScene, std::forward<TArgs>(initArgs)...); // std::mem_fn

			m_currScene->loadThis = false;
		}
	}

	template<class Scn>
	void SceneManager::changeScene(std::shared_ptr<Scn> newScene) {
		static_assert(std::is_base_of_v<Scene, Scn>, "Type Scn passed in is not Scene based");

		m_currScene = newScene;

		if (m_currScene->loadThis) {
			std::cerr << "Scn needs to be loaded, use function's other overload."<< std::endl
				        << "  Scn will remain unloaded for now" << std::endl;
		}
	}
}