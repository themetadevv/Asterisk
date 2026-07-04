#pragma once

/* Note :
	- This is a column major matrix data type.
	- C++ 20 or future version is required to use this data type in your project.
*/

template <typename T, int R, int C>
struct Matrix {
	T m[C][R];

	constexpr Matrix() :
		m { static_cast<T>(0) }
	{ }

	template <typename... ValueType> requires(sizeof...(ValueType) == R * C)
	constexpr Matrix(ValueType... values) :
		m { static_cast<T>(0) }
	{
		T data[] = { static_cast<T>(values)... };

		int value_index = 0;
		for (int c = 0; c < C; c++) {
			for (int r = 0; r < R; r++) {
				m[c][r] = data[value_index++];
			}
		}
	}

	static constexpr Matrix Identity()
		requires(R == C)
	{
		Matrix result;
		for (int i = 0; i < R; i++) {
			result.m[i][i] = static_cast<T>(1);
		}

		return result;
	}
};

template <typename T, int R, int I, int C>
constexpr Matrix<T, R, C> operator*(const Matrix<T, R, I>& a, const Matrix<T, I, C>& b) {
	Matrix<T, R, C> result;

	for (int c = 0; c < C; c++) {
		for (int r = 0; r < R; r++) {
			T sum = static_cast<T>(0);

			for (int k = 0; k < I; k++) {
				sum += a.m[k][r] * b.m[c][k];
			}

			result.m[c][r] = sum;
		}
	}

	return result;
}

// Aliases

using Matrix2x2 = Matrix<float, 2, 2>;
using Matrix2x3 = Matrix<float, 2, 3>;
using Matrix2x4 = Matrix<float, 2, 4>;

using Matrix3x2 = Matrix<float, 3, 2>;
using Matrix3x3 = Matrix<float, 3, 3>;
using Matrix3x4 = Matrix<float, 3, 4>;

using Matrix4x2 = Matrix<float, 4, 2>;
using Matrix4x3 = Matrix<float, 4, 3>;
using Matrix4x4 = Matrix<float, 4, 4>;