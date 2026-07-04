
// 2x2 * 2x2 = 2x2
inline constexpr Matrix2x2 operator*(const Matrix2x2& a, const Matrix2x2& b) {
	Matrix2x2 result;

	for (int c = 0; c < 2; c++) {
		for (int r = 0; r < 2; r++) {
			result.m[c][r] =
				a.m[0][r] * b.m[c][0] +
				a.m[1][r] * b.m[c][1];
		}
	}

	return result;
}

// 2x2 * 2x3 = 2x3
inline constexpr Matrix2x3 operator*(const Matrix2x2& a, const Matrix2x3& b) {
	Matrix2x3 result;

	for (int c = 0; c < 3; c++) {
		for (int r = 0; r < 2; r++) {
			result.m[c][r] =
				a.m[0][r] * b.m[c][0] +
				a.m[1][r] * b.m[c][1];
		}
	}

	return result;
}

// 2x2 * 2x4 = 2x4
inline constexpr Matrix2x4 operator*(const Matrix2x2& a, const Matrix2x4& b) {
	Matrix2x4 result;

	for (int c = 0; c < 4; c++) {
		for (int r = 0; r < 2; r++) {
			result.m[c][r] =
				a.m[0][r] * b.m[c][0] +
				a.m[1][r] * b.m[c][1];
		}
	}

	return result;
}

// 2x3 * 3x2 = 2x2
inline constexpr Matrix2x2 operator*(const Matrix2x3& a, const Matrix3x2& b) {
	Matrix2x2 result;

	for (int c = 0; c < 2; c++) {
		for (int r = 0; r < 2; r++) {
			result.m[c][r] =
				a.m[0][r] * b.m[c][0] +
				a.m[1][r] * b.m[c][1] +
				a.m[2][r] * b.m[c][2];
		}
	}

	return result;
}

// 2x3 * 3x3 = 2x3
inline constexpr Matrix2x3 operator*(const Matrix2x3& a, const Matrix3x3& b) {
	Matrix2x3 result;

	for (int c = 0; c < 3; c++) {
		for (int r = 0; r < 2; r++) {
			result.m[c][r] =
				a.m[0][r] * b.m[c][0] +
				a.m[1][r] * b.m[c][1] +
				a.m[2][r] * b.m[c][2];
		}
	}

	return result;
}

// 2x3 * 3x4 = 2x4
inline constexpr Matrix2x4 operator*(const Matrix2x3& a, const Matrix3x4& b) {
	Matrix2x4 result;

	for (int c = 0; c < 4; c++) {
		for (int r = 0; r < 2; r++) {
			result.m[c][r] = 
				a.m[0][r] * b.m[c][0] +
				a.m[1][r] * b.m[c][1] +
				a.m[2][r] * b.m[c][2];
		}
	}

	return result;
}

// 2x4 * 4x2 = 2x2
inline constexpr Matrix2x2 operator*(const Matrix2x4& a, const Matrix4x2& b) {
	Matrix2x2 result;

	for (int c = 0; c < 2; c++) {
		for (int r = 0; r < 2; r++) {
			result.m[c][r] =
				a.m[0][r] * b.m[c][0] +
				a.m[1][r] * b.m[c][1] +
				a.m[2][r] * b.m[c][2] +
				a.m[3][r] * b.m[c][3];
		}
	}

	return result;
}

// 2x4 * 4x3 = 2x3
inline constexpr Matrix2x3 operator*(const Matrix2x4& a, const Matrix4x3& b) {
	Matrix2x3 result;

	for (int c = 0; c < 3; c++) {
		for (int r = 0; r < 2; r++) {
			result.m[c][r] =
				a.m[0][r] * b.m[c][0] +
				a.m[1][r] * b.m[c][1] +
				a.m[2][r] * b.m[c][2] +
				a.m[3][r] * b.m[c][3];
		}
	}

	return result;
}

// 2x4 * 4x4 = 2x4
inline constexpr Matrix2x4 operator*(const Matrix2x4& a, const Matrix4x4& b) {
	Matrix2x4 result;

	for (int c = 0; c < 4; c++) {
		for (int r = 0; r < 2; r++) {
			result.m[c][r] =
				a.m[0][r] * b.m[c][0] +
				a.m[1][r] * b.m[c][1] +
				a.m[2][r] * b.m[c][2] +
				a.m[3][r] * b.m[c][3];
		}
	}

	return result;
}