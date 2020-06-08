#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <SDL.h>

namespace divengine
{
	class Font;
	class Texture2D;

	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color& color = {255,255,255});
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void SetText(const std::string& text);

	protected:
		void Update() override;
		void Render() override;
		void Initialize() override;


	private:
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		bool m_NeedsUpdate;
		SDL_Color m_Color;
	};
}
