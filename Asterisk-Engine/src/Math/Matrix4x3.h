#pragma once

// column-major
// rectangular matrix
struct Matrix4x3 {
	float m[3][4];

	constexpr Matrix4x3() : 
		m { 0.0f } 
	{ }

	constexpr Matrix4x3(
		float c0r0, float c1r0, float c2r0,
		float c0r1, float c1r1, float c2r1,
		float c0r2, float c1r2, float c2r2,
		float c0r3, float c1r3, float c2r3
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

		// third row
		m[0][2] = c0r2;
		m[1][2] = c1r2;
		m[2][2] = c2r2;

		// fourth row
		m[0][3] = c0r3;
		m[1][3] = c1r3;
		m[2][3] = c2r3;
	}
};