
#include "astpch.h"

#include "Core/NativeDialog.h"
#include "Logger/Logger.h"
#include "Utils/Utils.h"

#include "Engine/Platform/Api/OpenGL/gl_Debug.h"
#include "Engine/Platform/Api/OpenGL/gl_Shader.h"

namespace asterisk {
	static int GetOpenGLShaderType(ShaderType type) {
		switch (type) {
			case ShaderType::Vertex:   return GL_VERTEX_SHADER;
			case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
			case ShaderType::Geometry: return GL_GEOMETRY_SHADER;

			case ShaderType::Invalid:
			default:
				return -1;
		}
	}

	OpenGL_Shader::OpenGL_Shader(const std::string& path, bool has_geometry) :
		m_Path(path),
		m_HasGeometry(has_geometry)
	{
		ParseShaderFile();
		Load();
	}

	OpenGL_Shader::~OpenGL_Shader() {
		ClearProgram(m_ProgramID);
	}

	/*
		----------------
		PRIVATE METHODS
		----------------
	*/

	bool OpenGL_Shader::ShaderCompileSuccess(uint32_t shader, ShaderType type) {
		int status = 0;
		int log_msg_size = 0;
		char* log_buffer = 0;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_msg_size);
			log_buffer = new char[log_msg_size];
			glGetShaderInfoLog(shader, log_msg_size, nullptr, log_buffer);
			ASTR_ERROR(
				"[OpenGL_Shader] Failed to compile '{0}' shader. \nSource Path: '{1}'. \nLog Buffer: {2}",
				ShaderTypeString(type), m_Path, log_buffer
			);
			delete[] log_buffer;
			return false;
		}

		return true;
	}

	bool OpenGL_Shader::ProgramLinkSuccess(uint32_t program) {
		int status = 0;
		int log_msg_size = 0;
		char* log_buffer = 0;

		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_msg_size);
			log_buffer = new char[log_msg_size];
			glGetProgramInfoLog(program, log_msg_size, nullptr, log_buffer);
			ASTR_ERROR(
				"[OpenGL_Shader] Failed to link shader program. \nSource Path: '{0}'. \nLog Buffer: {1}",
				m_Path, 
				log_buffer
			);
			delete[] log_buffer;
			return false;
		}

		return true;
	}

	void OpenGL_Shader::ClearShaders() {
		if (m_VertexShaderID) {
			glDeleteShader(m_VertexShaderID);
			m_VertexShaderID = 0;
		}

		if (m_FragmentShaderID) {
			glDeleteShader(m_FragmentShaderID);
			m_FragmentShaderID = 0;
		}

		if (m_HasGeometry && m_GeometryShaderID) {
			glDeleteShader(m_GeometryShaderID);
			m_GeometryShaderID = 0;
		}
	}

	bool OpenGL_Shader::CompileShaders() {
		ClearShaders();

		// shaders source
		const char* vertex_shader_src   = m_ShaderSource[(int)ShaderType::Vertex].c_str();
		const char* fragment_shader_src = m_ShaderSource[(int)ShaderType::Fragment].c_str();

		// create & compile vertex shader
		m_VertexShaderID = glCreateShader(GetOpenGLShaderType(ShaderType::Vertex));
		glShaderSource(m_VertexShaderID, 1, &vertex_shader_src, nullptr);
		glCompileShader(m_VertexShaderID);
		if (!ShaderCompileSuccess(m_VertexShaderID, ShaderType::Vertex)) {
			ClearShaders();
			return false;
		}

		// create & compile fragment shader
		m_FragmentShaderID = glCreateShader(GetOpenGLShaderType(ShaderType::Fragment));
		glShaderSource(m_FragmentShaderID, 1, &fragment_shader_src, nullptr);
		glCompileShader(m_FragmentShaderID);
		if (!ShaderCompileSuccess(m_FragmentShaderID, ShaderType::Fragment)) {
			ClearShaders();
			return false;
		}

		// if geometry shader exists 
		// create & compile geometry shader
		if (m_HasGeometry) {
			const char* geometry_shader_src = m_ShaderSource[(int)ShaderType::Geometry].c_str();
			m_GeometryShaderID = glCreateShader(GetOpenGLShaderType(ShaderType::Geometry));
			glShaderSource(m_GeometryShaderID, 1, &geometry_shader_src, nullptr);
			glCompileShader(m_GeometryShaderID);
			if (!ShaderCompileSuccess(m_GeometryShaderID, ShaderType::Geometry)) {
				ClearShaders();
				return false;
			}
		}

		return true;
	}

	void OpenGL_Shader::ClearProgram(uint32_t& program) {
		if (program) {
			glDeleteProgram(program);
			program = 0;
		}
	}

	bool OpenGL_Shader::LinkProgram() {
		uint32_t new_program = glCreateProgram();

		// attach shaders
		glAttachShader(new_program, m_VertexShaderID);
		glAttachShader(new_program, m_FragmentShaderID);
		if (m_HasGeometry)
			glAttachShader(new_program, m_GeometryShaderID);

		// link program
		glLinkProgram(new_program);
		if (!ProgramLinkSuccess(new_program)) {
			ClearProgram(new_program);
			ClearShaders();
			return false;
		}

		// clear shaders after use
		ClearShaders();

		// delete old on success
		ClearProgram(m_ProgramID);
		m_Uniforms.clear();

		// assign new
		m_ProgramID = new_program;
		return true;
	}

	// TODO
	bool OpenGL_Shader::ParseShaderFile() {
		std::string src = utils::ReadFile(m_Path);
		if (src.empty()) {
			auto result = ShowErrorOccuredDialog(
				std::format("[OpenGL_Shader] shader source is empty! path: {}", m_Path)
			);

			if (result == DialogResult::OK) {
				TerminateProgram();
				return false;
			}
		}
			
		ShaderType type = ShaderType::Invalid;

		std::stringstream ss(src);
		std::string line;

		while (getline(ss, line)) {
			// check for windows cr
			if (!line.empty() && line.back() == '\r')
				line.pop_back();

			// ignore empty line
			if (line.empty())
				continue;

			// ignore comments
			if (line.starts_with("//"))
				continue;

			// shader selection
			if (line == ShaderTypeToken[(int)ShaderType::Vertex]) {
				type = ShaderType::Vertex;
				continue;
			}
			
			if (line == ShaderTypeToken[(int)ShaderType::Fragment]) {
				type = ShaderType::Fragment;
				continue;
			}

			if (line == ShaderTypeToken[(int)ShaderType::Geometry]) {
				type = ShaderType::Geometry;
				continue;
			}

			if (type == ShaderType::Invalid)
				continue;

			// ignore tokens
			if (line.starts_with(SHADER_TOKEN_START))
				continue;

			m_ShaderSource[(int)type] += line;
			m_ShaderSource[(int)type] += '\n';
		}

		return true;
	}

	int OpenGL_Shader::GetUniformLocation(const char* name) {
		auto it = m_Uniforms.find(name);
		if (it != m_Uniforms.end())
			return it->second;

		int loc = glGetUniformLocation(m_ProgramID, name);
		if (loc == INVALID_SHADER_LOCATION) {
			ASTR_WARN("[OpenGL_Shader] uniform '{0}' doesn't exist in shader '{1}'.", name, m_Path);
			return loc;
		}

		m_Uniforms[name] = loc;
		return loc;
	}

	/*
		----------------
		VIRTUAL METHODS
		----------------
	*/

	bool OpenGL_Shader::Load() {
		if (!CompileShaders())
			return false;

		if (!LinkProgram())
			return false;

		return true;
	}

	void OpenGL_Shader::Bind() const {
		glUseProgram(m_ProgramID);
	}

	void OpenGL_Shader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGL_Shader::SetInt(const char* name, int v) {
		glUniform1i(GetUniformLocation(name), v);
	}

	void OpenGL_Shader::SetFloat(const char* name, float v) {
		glUniform1f(GetUniformLocation(name), v);
	}

	void OpenGL_Shader::SetIntArray(const char* name, int count, int* v) {
		glUniform1iv(GetUniformLocation(name), count, v);
	}

	void OpenGL_Shader::SetVec2(const char* name, const Vector2& v) {
		glUniform2f(GetUniformLocation(name), v.x, v.y);
	}

	void OpenGL_Shader::SetVec3(const char* name, const Vector3& v) {
		glUniform3f(GetUniformLocation(name), v.x, v.y, v.z);
	}

	void OpenGL_Shader::SetVec4(const char* name, const Vector4& v) {
		glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w);
	}

	void OpenGL_Shader::SetMat4(const char* name, const Mat4& v) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, math::value_ptr(v));
	}
}
