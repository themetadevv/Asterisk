#pragma once

#include "Core/Common.h"

struct Vector2 {
	float x, y;

	constexpr Vector2() :
		x(0.0f), y(0.0f)
	{ }

	constexpr Vector2(float _x, float _y) :
		x(_x), y(_y)
	{ }

	constexpr Vector2 operator+(const Vector2& other) const {
		return {
			x + other.x,
			y + other.y
		};
	}

	constexpr Vector2 operator-(const Vector2& other) const {
		return {
			x - other.x,
			y - other.y
		};
	}

	constexpr Vector2 operator*(float scalar) const {
		return {
			x * scalar,
			y * scalar
		};
	}

	constexpr Vector2 operator/(float scalar) const {
		return {
			x / scalar,
			y / scalar
		};
	}
};