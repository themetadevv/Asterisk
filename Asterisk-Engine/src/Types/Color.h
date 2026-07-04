#pragma once

#include "Core/Common.h"

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

		ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) :
			r((float)_r / 255.0f), 
			g((float)_g / 255.0f), 
			b((float)_b / 255.0f), 
			a((float)_a / 255.0f)
		{ }

		ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b) :
			r((float)_r / 255.0f),
			g((float)_g / 255.0f),
			b((float)_b / 255.0f),
			a(1.0f)
		{ }
	};
}
