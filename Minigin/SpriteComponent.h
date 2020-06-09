#pragma once
#include "BaseComponent.h"
#include "SDL.h"
#include <string>

namespace divengine
{
	class RenderComponent;
	class TransformComponent;

	class SpriteComponent : public BaseComponent
	{
		public:
			SpriteComponent(const std::string& path, float width, float height, int nrOfFrames, float animationSpeed);
			~SpriteComponent();

		protected:
			virtual void Update() override;
			virtual void Initialize() override;
			virtual void Render() override;

			divengine::RenderComponent* m_pRenderComp;
			TransformComponent* m_pTransform;
			SDL_Rect srcRect, destRect;
			const int m_NrOfFrames;
			float m_AnimationSpeed; //number of frames per second
			bool m_EnableAnim;
			const std::string m_Path;

		private:
	};
}

