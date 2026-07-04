#pragma once

// column-major
// rectangular matrix
struct Matrix2x3 {
	float m[3][2];

	constexpr Matrix2x3() :
		m { 0.0f }
	{ }

	constexpr Matrix2x3(
		float c0r0, float c1r0, float c2r0,
		float c0r1, float c1r1, float c2r1
	) :
		m { 0.0f }
	{
		// first row
		m[0][0] = c0r0;
		m[1][0] = c1r0;
		m[2][0] = c2r0;

		// second row
		m[0][1] = c0r1;
		m[1][1] = c1r1;
		m[2][1] = c2r1;
	}
};