#pragma once

#include "Core/Common.h"

#include "Types/SmartPointers.h"

#include "Math/Math.h"

#include "Engine/Renderer/Enums.h"

#define INVALID_SHADER_ID -1
#define INVALID_SHADER_LOCATION -1

namespace asterisk {
	inline const char* ShaderTypeToken[] = {
		"$TYPE_VERTEX", 
		"$TYPE_FRAGMENT",
		"$TYPE_GEOMETRY"
	};

	class ASTERISK_ENGINE_API Shader {
	public:	
		virtual ~Shader() = default;

		virtual bool Load() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const char* name, int v) = 0;
		virtual void SetFloat(const char* name, float v) = 0;

		virtual void SetIntArray(const char* name, int count, int* v) = 0;

		virtual void SetVec2(const char* name, const Vector2& v) = 0;
		virtual void SetVec3(const char* name, const Vector3& v) = 0;
		virtual void SetVec4(const char* name, const Vector4& v) = 0;

		virtual void SetMat4(const char* name, const Mat4& v) = 0;

	public:
		static SharedPtr<Shader> Create(const char* path, bool has_geometry = false);
	};
}