#pragma once

// column-major
// square matrix
struct Matrix4x4 {
	float m[4][4]; // c-r

	constexpr Matrix4x4(
		float c0r0, float c1r0, float c2r0, float c3r0,
		float c0r1, float c1r1, float c2r1, float c3r1,
		float c0r2, float c1r2, float c2r2, float c3r2,
		float c0r3, float c1r3, float c2r3, float c3r3
	) :
		m {0.0f}
	{
		// first row
		m[0][0] = c0r0; 
		m[1][0] = c1r0;
		m[2][0] = c2r0;
		m[3][0] = c3r0; 

		// second row
		m[0][1] = c0r1;
		m[1][1] = c1r1;
		m[2][1] = c2r1;
		m[3][1] = c3r1;

		// third row
		m[0][2] = c0r2;
		m[1][2] = c1r2;
		m[2][2] = c2r2;
		m[3][2] = c3r2;

		// fourth row
		m[0][3] = c0r3;
		m[1][3] = c1r3;
		m[2][3] = c2r3;
		m[3][3] = c3r3;
	}

	// identity
	constexpr Matrix4x4(float diagnonal) :
		m {0.0f}
	{
		m[0][0] = diagnonal; // c0r1
		m[1][1] = diagnonal; // c1r2
		m[2][2] = diagnonal; // c2r3
		m[3][3] = diagnonal; // c3r4
	}

	constexpr Matrix4x4 operator*(const Matrix4x4& v) const {
		Matrix4x4 result(0.0f);

		for (int c = 0; c < 4; c++) {
			for (int r = 0; r < 4; r++) {
				result.m[c][r] =
					m[0][r] * v.m[c][0] +
					m[1][r] * v.m[c][1] +
					m[2][r] * v.m[c][2] +
					m[3][r] * v.m[c][3]; 
			}
		}

		return result;
	}
};