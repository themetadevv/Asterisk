#pragma once

#include "Math/Matrix2x2.h"
#include "Math/Matrix2x3.h"
#include "Math/Matrix2x4.h"

#include "Math/Matrix3x2.h"
#include "Math/Matrix3x3.h"
#include "Math/Matrix3x4.h"

#include "Math/Matrix4x2.h"
#include "Math/Matrix4x3.h"
#include "Math/Matrix4x4.h"

// 2x2 * 2x2 = 2x2
constexpr Matrix2x2 operator*(const Matrix2x2& a, const Matrix2x2& b);

// 2x2 * 2x3 = 2x3
constexpr Matrix2x3 operator*(const Matrix2x2& a, const Matrix2x3& b);

// 2x2 * 2x4 = 2x4
constexpr Matrix2x4 operator*(const Matrix2x2& a, const Matrix2x4& b);

// 2x3 * 3x2 = 2x2
constexpr Matrix2x2 operator*(const Matrix2x3& a, const Matrix3x2& b);

// 2x3 * 3x3 = 2x3
constexpr Matrix2x3 operator*(const Matrix2x3& a, const Matrix3x3& b);

// 2x3 * 3x4 = 2x4
constexpr Matrix2x4 operator*(const Matrix2x3& a, const Matrix3x4& b);

// 2x4 * 4x2 = 2x2
constexpr Matrix2x2 operator*(const Matrix2x4& a, const Matrix4x2& b);

// 2x4 * 4x3 = 2x3
constexpr Matrix2x3 operator*(const Matrix2x4& a, const Matrix4x3& b);

// 2x4 * 4x4 = 2x4
constexpr Matrix2x4 operator*(const Matrix2x4& a, const Matrix4x4& b);

// todo: impl 3 and 4 row matrices operator

#include "Math/Row2_Matrix_Operators.inl"