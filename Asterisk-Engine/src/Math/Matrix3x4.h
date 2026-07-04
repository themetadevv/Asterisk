#pragma once

// column-major
// rectangular matrix
struct Matrix3x4 {
	float m[4][3];

	constexpr Matrix3x4() : 
		m {0.0f}
	{ }

	constexpr Matrix3x4(
		float c0r0, float c1r0, float c2r0, float c3r0,
		float c0r1, float c1r1, float c2r1, float c3r1,
		float c0r2, float c1r2, float c2r2, float c3r2
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
	}
};