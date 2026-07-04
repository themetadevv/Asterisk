#pragma once

// column-major
// square matrix
struct Matrix3x3 {
	float m[3][3];

	constexpr Matrix3x3() : 
		m {0.0f}
	{ }

	constexpr Matrix3x3(
		float c0r0, float c1r0, float c2r0,
		float c0r1, float c1r1, float c2r1,
		float c0r2, float c1r2, float c2r2
	) :
		m{ 0.0f }
	{
		// first row
		m[0][0] = c0r0;
		m[1][0] = c1r0;
		m[2][0] = c2r0;

		// second row
		m[0][1] = c0r1;
		m[1][1] = c1r1;
		m[2][1] = c2r1;

		// third row
		m[0][2] = c0r2;
		m[1][2] = c1r2;
		m[2][2] = c2r2;
	}

	constexpr Matrix3x3(float diagonal) 
		: m {0.0f} 
	{
		m[0][0] = diagonal;
		m[1][1] = diagonal;
		m[2][2] = diagonal;
	}

	constexpr Matrix3x3 operator*(const Matrix3x3& v) {
		Matrix3x3 result;

		for (int c = 0; c < 3; c++) {
			for (int r = 0; r < 3; r++) {
				result.m[c][r] =
					m[0][r] * v.m[c][0] +
					m[1][r] * v.m[c][1] + 
					m[2][r] * v.m[c][2];
			}
		}

		return result;
	}
};