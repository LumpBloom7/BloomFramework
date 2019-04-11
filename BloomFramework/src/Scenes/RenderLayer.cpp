#include "Scenes/RenderLayer.h"
#include "Game.h"

namespace bloom {
	RenderLayer::RenderLayer(Game& gameInstance) : 
		m_gameInstance(gameInstance),
		m_layerRotateCenter(Coord().toSDLPoint(m_gameInstance.getRenderer())) {
		int w, h;
		SDL_RenderGetLogicalSize(m_gameInstance.getRenderer(), &w, &h);
		m_layerTexture = SDL_CreateTexture(m_gameInstance.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

		SDL_SetTextureBlendMode(m_layerTexture, SDL_BLENDMODE_BLEND);
	}
	RenderLayer::~RenderLayer() {
		SDL_DestroyTexture(m_layerTexture);
	}

	void RenderLayer::target(){
		SDL_SetRenderTarget(m_gameInstance.getRenderer(), m_layerTexture);
	}

	void RenderLayer::untarget(){
		SDL_SetRenderTarget(m_gameInstance.getRenderer(), nullptr);
	}

	void RenderLayer::draw() {
		SDL_RenderCopyEx(m_gameInstance.getRenderer(), m_layerTexture, nullptr, nullptr, m_layerRotateAngle, &m_layerRotateCenter, SDL_FLIP_NONE);
	}

	void RenderLayer::setLayerRotation(double angle) {
		m_layerRotateAngle = fmod(angle, 360.0);
	}

	void RenderLayer::adjustLayerRotation(double adjustment) {
		m_layerRotateAngle = fmod((m_layerRotateAngle + adjustment), 360.0);
	}

	double RenderLayer::getLayerRotation() {
		return m_layerRotateAngle;
	}

	void RenderLayer::setLayerRotationCenter(Coord center) {
		m_layerRotateCenter = center.toSDLPoint(m_gameInstance.getRenderer());
	}

	void RenderLayer::setLayerRotationCenter(SDL_Point center) {
		m_layerRotateCenter = center;
	}
}