#pragma once
#include "stdIncludes.h"
#include "../Coord.h"

namespace bloom {
	class Game;
	class BLOOMFRAMEWORK_API RenderLayer {
	public:
		RenderLayer(Game& gameInstance);
		~RenderLayer();

		void target();
		void untarget();
		void draw();

		void setLayerRotation(double angle);
		void adjustLayerRotation(double adjustment);
		double getLayerRotation();
		void setLayerRotationCenter(Coord center);
		void setLayerRotationCenter(SDL_Point center);

	private:
		Game& m_gameInstance;
		SDL_Texture* m_layerTexture = nullptr;

		double m_layerRotateAngle = 0.0;
		SDL_Point m_layerRotateCenter;
	};
}