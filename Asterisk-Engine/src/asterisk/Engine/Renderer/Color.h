#pragma once

#include "asterisk/Core/Common.h"

namespace asterisk {
	struct ColorRGBA {
		float r, g, b, a;

		ColorRGBA() :
			r(1.0f), g(1.0f), b(1.0f), a(1.0f)
		{ }

		explicit ColorRGBA(uint8_t v) {
			float _v = (float)v;

			r = _v / 255.0f;
			g = _v / 255.0f;
			b = _v / 255.0f;
			a = _v / 255.0f;
		}

		explicit ColorRGBA(float v) :
			r(v), g(v), b(v), a(v)
		{ }

		ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) :
			r((float)_r), 
			g((float)_g), 
			b((float)_b), 
			a((float)_a)
		{ }

		ColorRGBA(float _r, float _g, float _b, float _a) :
			r(_r), g(_g), b(_b), a(_a)
		{ }
	};
}
