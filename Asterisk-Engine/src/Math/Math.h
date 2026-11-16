#pragma once

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

#include "Math/Matrix.h"
#include "Math/MatrixAliases.h"

namespace asterisk::math {
	/*
		Matrix
	*/

	template <typename T, int R, int C>
	inline constexpr T* value_ptr(Matrix<T, R, C>& v) {
		return &v.m[0][0];
	}

	template <typename T, int R, int C>
	inline constexpr const T* value_ptr(const Matrix<T, R, C>& v) {
		return &v.m[0][0];
	}

	/*
		Vector
	*/

	inline constexpr float* value_ptr(Vector2& v) {
		return &v.x;
	}

	inline constexpr const float* value_ptr(const Vector2& v) {
		return &v.x;
	}
}