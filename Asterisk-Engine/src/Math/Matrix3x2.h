#pragma once

// column-major
// rectangular matrix
struct Matrix3x2 {
	float m[2][3];

	constexpr Matrix3x2() :
		m { 0.0f }
	{ }

	constexpr Matrix3x2(
		float c0r0, float c1r0,
		float c0r1, float c1r1,
		float c0r2, float c1r2
	) :
		m { 0.0f }
	{
		// first row
		m[0][0] = c0r0;
		m[1][0] = c1r0;

		// second row
		m[0][1] = c0r1;
		m[1][1] = c1r1;

		// third row
		m[0][2] = c0r2;
		m[1][2] = c1r2;
	}
};