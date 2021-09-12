#include "pch/wavepch.h"
#include "shader.h"

namespace Wave
{
	Shader::Shader() : mProgramId(0)
	{
	}

	Shader::~Shader()
	{
		glDeleteProgram(mProgramId);
	}

	bool Shader::Load(const std::string filename)
	{
		const char* c_assets_dir = TOSTRING(ASSETS_DIR);
		std::string assets_dir(c_assets_dir);
		std::string shader_dir = assets_dir + "/shaders/";

		std::string vert_file_loc = shader_dir + filename + ".vert";
		std::string vert_shader = String::get_file_contents(vert_file_loc.c_str());

		std::string frag_file_loc = shader_dir + filename + ".frag";
		std::string frag_shader = String::get_file_contents(frag_file_loc.c_str());

		TRACE("Loading Shader: {} -> {}, {}", filename, vert_file_loc, frag_file_loc);

		GLuint vert_id = CompileShader(GL_VERTEX_SHADER, vert_shader);
		GLuint frag_id = CompileShader(GL_FRAGMENT_SHADER, frag_shader);

		if (!vert_id || !frag_id)
		{
			return false;
		}

		LinkShader(vert_id, frag_id);

		return true;
	}

	GLuint Shader::CompileShader(GLenum shader_type, const std::string& file)
	{
		GLuint shader_id = glCreateShader(shader_type);

		const char* src = file.c_str();
		glShaderSource(shader_id, 1, &src, nullptr);

		glCompileShader(shader_id);

		GLint succes = 0;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &succes);
		if (succes == GL_FALSE)
		{
			GLint max_length = 0;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

			// The max_length includes the NULL character
			std::vector<GLchar> error_log(max_length);
			glGetShaderInfoLog(shader_id, max_length, &max_length, &error_log[0]);

			// Provide the infolog in whatever manner you deem best.
			// Exit with failure.
			glDeleteShader(shader_id); // Don't leak the Shader.

			ERROR("Shader failed to compile: {}", file);
			ERROR(&(error_log[0]));
			return false;
		}
		return shader_id;
	}

	void Shader::LinkShader(GLuint& vert_id, GLuint& frag_id)
	{
		mProgramId = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(mProgramId, vert_id);
		glAttachShader(mProgramId, frag_id);

		// Link our program
		glLinkProgram(mProgramId);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint succes(0);
		glGetProgramiv(mProgramId, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			GLint max_length(0);
			glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &max_length);

			// The max_length includes the NULL character
			std::vector<GLchar> error_log(max_length);
			glGetProgramInfoLog(mProgramId, max_length, &max_length, &error_log[0]);

			// We don't need the program anymore.
			glDeleteProgram(mProgramId);
			// Don't leak shaders either.
			glDeleteShader(vert_id);
			glDeleteShader(frag_id);

			// Use the infoLog as you see fit.
			ERROR("Shader failed to link");
			ERROR(&(error_log[0]));

			return;
		}

		// Always detach and delete shaders after a successful link.
		glDetachShader(mProgramId, vert_id);
		glDetachShader(mProgramId, frag_id);
		glDeleteShader(vert_id);
		glDeleteShader(frag_id);
	}

	void Shader::Begin()
	{
		glUseProgram(mProgramId);
	}

	void Shader::End()
	{
		glUseProgram(0);
	}

	GLuint Shader::GetUniformLocation(const std::string name)
	{
		GLuint location = glGetUniformLocation(mProgramId, name.c_str());
		if (location == GL_INVALID_INDEX)
		{
			ERROR("Uniform variable not found in Shader: {}", name);
		}
		return location;
	}

	void Shader::SetInt(const char* name, const int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetFloat(const char* name, const float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetVec2(const char* name, float x, float y)
	{
		glUniform2f(GetUniformLocation(name), x, y);
	}

	void Shader::SetVec2(const char* name, glm::vec2 vector)
	{
		glUniform2fv(GetUniformLocation(name), 1, &vector[0]);
	}

	void Shader::SetVec3(const char* name, float x, float y, float z)
	{
		glUniform3f(GetUniformLocation(name), x, y, z);
	}

	void Shader::SetVec3(const char* name, glm::vec3 vector)
	{
		glUniform3fv(GetUniformLocation(name), 1, &vector[0]);
	}

	void Shader::SetVec4(const char* name, glm::vec4 vector)
	{
		glUniform4fv(GetUniformLocation(name), 1, &vector[0]);
	}

	void Shader::SetVec4(const char* name, float x, float y, float z, float w)
	{
		glUniform4f(GetUniformLocation(name), x, y, z, w);
	}

	void Shader::SetMat4(const char* name, glm::mat4 const matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}
}