#include "Scenes\Scene.h"
#include "Scenes\SceneManager.h"
#include "Game.h"

namespace bloom {
	Scene::Scene(SceneManager& sceneManager) :
		m_sceneManager(sceneManager),
		m_gameInstance(sceneManager.m_gameInstance)
	{
		createRenderLayer();
	}

	void Scene::update(double deltaTime) {
		m_renderLayers[0].target();
		SDL_SetRenderDrawColor(m_gameInstance.getRenderer(), 0, 0, 0, 0);
		SDL_RenderClear(m_gameInstance.getRenderer());
		for (auto& sys : m_systems)
			if (sys->enabled)
				sys->update(deltaTime);
		m_renderLayers[0].untarget();
	}

	void Scene::draw() {
		for (auto renderLayer : m_renderLayers)
			renderLayer.draw();
	}

	void Scene::start() {
		load();
		m_sceneLoaded = true;
	}

	void Scene::restart() {
		unregisterAllSystems();
		destroyAllGameObjects();
		load();
		m_sceneLoaded = true;
	}

	void Scene::createRenderLayer(int amount) {
		for (int i = 0; i < amount; ++i)
			m_renderLayers.emplace_back(RenderLayer(m_gameInstance));
	}

	void Scene::destroyGameObject(const std::string & tag) {
		m_gameObjects.erase(tag);
	}

	void Scene::destroyAllGameObjects() {
		m_gameObjects.clear();
	}

	void Scene::unregisterAllSystems() {
		m_systems.clear();
	}
}

