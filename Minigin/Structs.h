#pragma once
#pragma warning(push)
#pragma warning(disable : 4201)
#include "glm/common.hpp"
#pragma warning(pop)
#include "SDL.h"

namespace divengine
{
	class ColliderComponent;

	struct Vector2
	{
		Vector2(float X = 0.f, float Y = 0.f) : x{ X }, y{ Y }{}
		float x,y;
	};

	struct Vector3
	{
		Vector3(float X = 0.f, float Y = 0.f, float Z = 0.f) : x{ X }, y{ Y }, z{ Z }{}
		float x,y,z;
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

	inline void Clamp(float& value, float min, float max)
	{
		if (value > max)
			value = max;

		if (value < min)
			value = min;
	}

	inline bool AlmostEquals(float value1, float value2)
	{
		return abs(value1 - value2) < 0.001f;
	}

	inline float SquaredDistance(const glm::vec2& v1, const glm::vec2& v2)
	{
		float Xdist = v1.x - v2.x;
		float YDist = v1.y - v2.y;
		return { Square(Xdist) + Square(YDist) };
	}

	inline float Distance(const glm::vec2& v1, const glm::vec2& v2)
	{
		return sqrt(SquaredDistance(v1, v2));
	}

	struct HitInfo
	{
		//glm::vec2 IntersectPoint;
		//glm::vec2 Normal;
		float distance;
		ColliderComponent* pCollider;
	};

	struct Line
	{
		glm::vec2 p1;
		glm::vec2 p2;
	};

	bool HorizontalRaycast(const glm::vec2& origin, float rayLength, const glm::vec2& dir, HitInfo& hitInfo);
}