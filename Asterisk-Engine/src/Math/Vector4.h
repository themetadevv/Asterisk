#pragma once

#include "Core/Common.h"

struct Vector4 {
	float x, y, z, w;

	constexpr Vector4() :
		x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	constexpr Vector4(float _x, float _y, float _z, float _w) :
		x(_x), y(_y), z(_z), w(_w)
	{
	}

	constexpr Vector4 operator+(const Vector4& other) const {
		return {
			x + other.x,
			y + other.y,
			z + other.z,
			w + other.w
		};
	}

	constexpr Vector4 operator-(const Vector4& other) const {
		return {
			x - other.x,
			y - other.y,
			z - other.z,
			w - other.w
		};
	}

	constexpr Vector4 operator*(float scalar) const {
		return {
			x * scalar,
			y * scalar,
			z * scalar,
			w * scalar
		};
	}

	constexpr Vector4 operator/(float scalar) const {
		return {
			x / scalar,
			y / scalar,
			z / scalar,
			w / scalar
		};
	}
};