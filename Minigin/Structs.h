#pragma once
#pragma warning(push)
#pragma warning(disable : 4201)
#include "glm/common.hpp"
#pragma warning(pop)
#include "SDL.h"

namespace divengine
{
	struct Vector2
	{
		Vector2(float X = 0.f, float Y = 0.f) : x{ X }, y{ Y }{}
		float x;
		float y;
	};

	struct Vector3
	{
		Vector3(float X = 0.f, float Y = 0.f, float Z = 0.f) : x{ X }, y{ Y }, z{ Z }{}
		float x;
		float y;
		float z;
	};

	struct Circlef
	{
		Circlef() :center{0.f,0.f}, radius{0.f} {}
		Circlef(const glm::vec2& c, float r): center{c},radius{r}{}
		glm::vec2 center;
		float radius;
	};

	struct Rectf
	{
		Rectf() :bottomLeft{0.f, 0.f}, width{0.f}, height{0.f} {}
		Rectf(const glm::vec2& bottomleft, float w, float h) :bottomLeft{bottomleft}, width{w}, height{h} {}
		glm::vec2 bottomLeft;
		float width, height;

		inline Rectf operator=(const SDL_Rect& pos)
		{
			bottomLeft.x = (float)pos.x;
			bottomLeft.y = (float)pos.y;
			width = (float)pos.w;
			height = (float)pos.h;
		}
	};

	inline SDL_Rect RectfToSDLRect(const divengine::Rectf& rectf)
	{
		SDL_Rect rect{};
		rect.x = (int)rectf.bottomLeft.x;
		rect.y = (int)rectf.bottomLeft.y;
		rect.w = (int)rectf.width;
		rect.h = (int)rectf.height;
		return rect;
	}

	inline float Square(float a)
	{
		return a * a;
	}
}