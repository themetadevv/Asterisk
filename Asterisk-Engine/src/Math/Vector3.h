#pragma once

#include "Core/Common.h"

struct Vector3 {
	float x, y, z;

	constexpr Vector3() :
		x(0.0f), y(0.0f), z(0.0f)
	{
	}

	constexpr Vector3(float _x, float _y, float _z) :
		x(_x), y(_y), z(_z)
	{
	}

	constexpr Vector3 operator+(const Vector3& other) const {
		return {
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	constexpr Vector3 operator-(const Vector3& other) const {
		return {
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	constexpr Vector3 operator*(float scalar) const {
		return {
			x * scalar,
			y * scalar,
			z * scalar
		};
	}

	constexpr Vector3 operator/(float scalar) const {
		return {
			x / scalar,
			y / scalar,
			z / scalar
		};
	}
};