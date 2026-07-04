#pragma once

#include "Core/Common.h"
#include "Math/Math.h"
#include "Engine/Input/InputCode.h"

DISABLE_ALL_WARNING
#include <spdlog/fmt/fmt.h>
RESET_WARNING

template <>
struct fmt::formatter<Vector2> {
	constexpr auto parse(fmt::format_parse_context& ctx) {
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const Vector2& v, FormatContext& ctx) const {
		return fmt::format_to(ctx.out(), "({}, {})", v.x, v.y);
	}
};

template <>
struct fmt::formatter<Vector3> {
	constexpr auto parse(fmt::format_parse_context& ctx) {
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const Vector3& v, FormatContext& ctx) const {
		return fmt::format_to(ctx.out(), "({}, {}, {})", v.x, v.y, v.z);
	}
};

template <>
struct fmt::formatter<Vector4> {
	constexpr auto parse(fmt::format_parse_context& ctx) {
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const Vector4& v, FormatContext& ctx) const {
		return fmt::format_to(ctx.out(), "({}, {}, {}, {})", v.x, v.y, v.z, v.w);
	}
};

template<>
struct fmt::formatter<KeyCode> {
	constexpr auto parse(fmt::format_parse_context& ctx) {
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const KeyCode& v, FormatContext& ctx) const {
		return fmt::format_to(ctx.out(), "{}", (int)v);
	}
};