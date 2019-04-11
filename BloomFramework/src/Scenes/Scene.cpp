#include "Scenes\Scene.h"
#include "Scenes\SceneManager.h"
#include "Game.h"

namespace bloom {
	Scene::Scene(SceneManager & sceneManager) :
		m_sceneManager(sceneManager),
		m_gameInstance(sceneManager.m_gameInstance),
		m_sceneRotateCenter(Coord().toSDLPoint(m_gameInstance.getRenderer()))
	{
		createRenderLayer();
	}

	Scene::~Scene() {
		for(auto renderLayer : m_renderLayers)
		SDL_DestroyTexture(renderLayer);
	}

	void Scene::update(double deltaTime) {
		SDL_SetRenderTarget(m_gameInstance.getRenderer(), m_renderLayers[0]); // Render everything on the first layer by default
		SDL_SetRenderDrawColor(m_gameInstance.getRenderer(), 0, 0, 0, 0);
		SDL_RenderClear(m_gameInstance.getRenderer());
		for (auto & sys : m_systems)
			if (sys->enabled)
				sys->update(deltaTime);
		SDL_SetRenderTarget(m_gameInstance.getRenderer(), nullptr);
	}

	void Scene::draw() {
		for(auto renderLayer : m_renderLayers)
			SDL_RenderCopyEx(m_gameInstance.getRenderer(), renderLayer, nullptr, nullptr, m_sceneRotateAngle, &m_sceneRotateCenter, SDL_FLIP_NONE);
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
		for (int i = 0; i < amount; ++i) {
			SDL_Texture* renderLayer = SDL_CreateTexture(m_gameInstance.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
				m_gameInstance.getScreenWidth(),
				m_gameInstance.getScreenHeight());

			SDL_SetTextureBlendMode(renderLayer, SDL_BLENDMODE_BLEND);
			m_renderLayers.emplace_back(renderLayer);
		}
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

	void Scene::setSceneRotation(double angle) {
		m_sceneRotateAngle = fmod(angle, 360.0);
	}

	void Scene::adjustSceneRotation(double adjustment) {
		m_sceneRotateAngle = fmod((m_sceneRotateAngle + adjustment), 360.0);
	}

	double Scene::getSceneRotation() {
		return m_sceneRotateAngle;
	}

	void Scene::setSceneRotationCenter(Coord center) {
		m_sceneRotateCenter = center.toSDLPoint(m_gameInstance.getRenderer());
	}

	void Scene::setSceneRotationCenter(SDL_Point center) {
		m_sceneRotateCenter = center;
	}
}

