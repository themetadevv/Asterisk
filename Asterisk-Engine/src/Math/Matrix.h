#pragma once

/* Note :
	- This is a column major matrix data type.
	- C++ 20 or future version is required to use this data type in your project.
*/

template <typename T, int R, int C>
struct Matrix {
	T m[C][R];

	constexpr Matrix() :
		m {  }
	{ }

	template <typename... ValueType> requires(sizeof...(ValueType) == R * C)
	constexpr Matrix(ValueType... values) :
		m {  }
	{
		T data[] = { static_cast<T>(values)... };

		int value_index = 0;
		for (int c = 0; c < C; c++) {
			for (int r = 0; r < R; r++) {
				m[c][r] = data[value_index++];
			}
		}
	}

	
	constexpr Matrix(T diagonal) 
		requires(R == C)
		: m {  } 
	{
		for (int i = 0; i < R; i++) {
			m[i][i] = diagonal;
		}
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