#pragma once

#include "Math/Matrix.h"

// column major

using Matrix2x2 = Matrix<float, 2, 2>;
using Matrix2x3 = Matrix<float, 2, 3>;
using Matrix2x4 = Matrix<float, 2, 4>;

using Matrix3x2 = Matrix<float, 3, 2>;
using Matrix3x3 = Matrix<float, 3, 3>;
using Matrix3x4 = Matrix<float, 3, 4>;

using Matrix4x2 = Matrix<float, 4, 2>;
using Matrix4x3 = Matrix<float, 4, 3>;
using Matrix4x4 = Matrix<float, 4, 4>;

using Mat2 = Matrix2x2;
using Mat3 = Matrix3x3;
using Mat4 = Matrix4x4;