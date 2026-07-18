#pragma once

#include "Core/Common.h"
#include "Types/Containers.h"

#include "Engine/Renderer/Shader.h"

namespace asterisk {
	class OpenGL_Shader : public Shader {
	private:
		std::string m_Path;
		std::string m_ShaderSource[3];

		UnorderedMap<std::string, int> m_Uniforms;

		uint32_t m_VertexShaderID;
		uint32_t m_FragmentShaderID;
		uint32_t m_GeometryShaderID;

		uint32_t m_ProgramID;

		bool m_HasGeometry;

	public:
		OpenGL_Shader(const std::string& path, bool has_geometry);
		~OpenGL_Shader() override;

	private:
		bool ShaderCompileSuccess(uint32_t shader, ShaderType type);
		bool ProgramLinkSuccess(uint32_t program);

		void ClearShaders();
		bool CompileShaders();

		void ClearProgram(uint32_t& program);
		bool LinkProgram();

		bool ParseShaderFile();

		int GetUniformLocation(const char* name);
		
	public:
		bool Load() override;

		void Bind() const override;
		void Unbind() const override;

		void SetInt(const char* name, int v) override;
		void SetFloat(const char* name, float v) override;

		void SetIntArray(const char* name, int count, int* v) override;

		void SetVec2(const char* name, const Vector2& v) override;
		void SetVec3(const char* name, const Vector3& v) override;
		void SetVec4(const char* name, const Vector4& v) override;

		void SetMat4(const char* name, const Mat4& v) override;
	};
}