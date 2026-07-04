#pragma once

// column-major
// square matrix
struct Matrix2x2 {
	float m[2][2];

	constexpr Matrix2x2() :
		m { 0.0f }
	{ }

	constexpr Matrix2x2(float diagonal) :
		m { 0.0f }
	{ 
		m[0][0] = 1.0f;
		m[1][1] = 1.0f;
	}

	constexpr Matrix2x2(
		float c0r0, float c1r0,
		float c0r1, float c1r1
	) :
		m { 0.0f }
	{
		// first row
		m[0][0] = c0r0;
		m[1][0] = c1r0;

		// second row
		m[0][1] = c0r1;
		m[1][1] = c1r1;
	}
};