#pragma once
#include "Structs.h"
#include "BaseComponent.h"

struct SDL_Texture;
namespace dae
{
	class Texture2D;

	//Does 2D rendering
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent();
		RenderComponent(const std::string& filename);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
		void SetTexture(const std::string& filename);
		void SetTexture(SDL_Texture* texture);

	protected:
		void Update(float MsPerUpdate) override;
		void Render() override;

	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};

}