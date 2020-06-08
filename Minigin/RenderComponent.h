#pragma once
#include "Structs.h"
#include "BaseComponent.h"

struct SDL_Texture;
namespace divengine
{
	class Texture2D;

	//Does 2D rendering
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent();
		RenderComponent(const std::string& filename);
		virtual ~RenderComponent();
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
		void SetTexture(const std::string& filename);
		void SetTexture(SDL_Texture* texture);
		void SetSourceRect(SDL_Rect& srcRect);
		void SetDestRect(SDL_Rect& destRect);
		Vector2 GetTextureDimensions() const;

	protected:
		void Update() override;
		void Render() override;
		void Initialize() override;

	private:
		std::shared_ptr<Texture2D> m_Texture{};
		SDL_Rect* m_SrcRect;
		SDL_Rect* m_DestRect;
	};

}