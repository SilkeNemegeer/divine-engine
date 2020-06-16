#pragma once
#include <vector>
#include "AnimationClip.h"
#include "BaseComponent.h"

namespace divengine
{
	class RenderComponent;
	class TransformComponent;

	class Animator : public BaseComponent //Is base component?
	{
		public:
			Animator(const std::string& path, float clipHeight, float clipWidth);
			~Animator();
			void SetAnimation(AnimationClip* animation);
			void SetAnimation(const std::string& name);
			void AddAnimation(AnimationClip* animation);

			void Restart();
			void Play();
			void Pause();
			void SetAnimSpeed(float animationSpeed) { m_AnimationSpeed = animationSpeed; };
			float GetAnimSpeed() const { return m_AnimationSpeed; };
			bool IsPlaying() const { return m_IsPlaying; };

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void PostInitialize() override;
		virtual void Render() override;

		private:
			std::vector<AnimationClip*> m_pAnimations;
			AnimationClip* m_pCurrentAnimation;

			bool m_IsPlaying;
			float m_AnimationSpeed;
			int m_CurrentFrame;
			float m_CurrentFrameTime;

			RenderComponent* m_pRenderComp;
			TransformComponent* m_pTransform;
			SDL_Rect m_SrcRect, m_DestRect;
			int m_Cols, m_Rows;
			std::string m_Path;
			float m_ClipHeight, m_ClipWidth;

	};
}
