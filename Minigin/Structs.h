#pragma once

namespace dae
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
}