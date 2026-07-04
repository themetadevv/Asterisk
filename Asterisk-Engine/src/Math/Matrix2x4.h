#pragma once

// column-major
// rectangular matrix
struct Matrix2x4 {
	float m[4][2];

	constexpr Matrix2x4() :
		m { 0.0f }
	{ }

	constexpr Matrix2x4(
		float c0r0, float c1r0, float c2r0, float c3r0,
		float c0r1, float c1r1, float c2r1, float c3r1
	) :
		m { 0.0f }
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
	}
};