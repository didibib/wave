#include "wavepch.h"
#include "shader.h"

namespace wave
{
	shader::shader() : m_program_id(0)
	{
	}

	shader::~shader()
	{
		glDeleteProgram(m_program_id);
	}

	bool shader::load(const std::string filename)
	{
		std::string vert_file_loc = "assets/shaders/" + filename + ".vert";
		std::string vert_shader = string::get_file_contents(vert_file_loc.c_str());

		std::string frag_file_loc = "assets/shaders/" + filename + ".frag";
		std::string frag_shader = string::get_file_contents(frag_file_loc.c_str());

		TRACE("Loading shader: {} -> {}, {}", filename, vert_file_loc, frag_file_loc);

		GLuint vert_id = compile_shader(GL_VERTEX_SHADER, vert_shader);
		GLuint frag_id = compile_shader(GL_FRAGMENT_SHADER, frag_shader);

		if (!vert_id || !frag_id)
		{
			return false;
		}

		link_shader(vert_id, frag_id);

		return true;
	}

	GLuint shader::compile_shader(GLenum shader_type, const std::string& file)
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
			glDeleteShader(shader_id); // Don't leak the shader.

			ERROR("Shader failed to compile: {}", file);
			ERROR(&(error_log[0]));
			return false;
		}
		return shader_id;
	}

	void shader::link_shader(GLuint& vert_id, GLuint& frag_id)
	{
		m_program_id = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_program_id, vert_id);
		glAttachShader(m_program_id, frag_id);

		// Link our program
		glLinkProgram(m_program_id);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint succes(0);
		glGetProgramiv(m_program_id, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			GLint max_length(0);
			glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &max_length);

			// The max_length includes the NULL character
			std::vector<GLchar> error_log(max_length);
			glGetProgramInfoLog(m_program_id, max_length, &max_length, &error_log[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_program_id);
			// Don't leak shaders either.
			glDeleteShader(vert_id);
			glDeleteShader(frag_id);

			// Use the infoLog as you see fit.
			ERROR("Shader failed to link");
			ERROR(&(error_log[0]));

			return;
		}

		// Always detach and delete shaders after a successful link.
		glDetachShader(m_program_id, vert_id);
		glDetachShader(m_program_id, frag_id);
		glDeleteShader(vert_id);
		glDeleteShader(frag_id);
	}

	void shader::begin()
	{
		glUseProgram(m_program_id);
	}

	void shader::end()
	{
		glUseProgram(0);
	}

	GLuint shader::get_uniform_location(const std::string name)
	{
		GLuint location = glGetUniformLocation(m_program_id, name.c_str());
		if (location == GL_INVALID_INDEX)
		{
			ERROR("Uniform variable not found in shader: {}", name);
		}
		return location;
	}

	void shader::set_int(const char* name, const int value)
	{
		glUniform1i(get_uniform_location(name), value);
	}

	void shader::set_float(const char* name, const float value)
	{
		glUniform1f(get_uniform_location(name), value);
	}

	void shader::set_vec2(const char* name, float x, float y)
	{
		glUniform2f(get_uniform_location(name), x, y);
	}

	void shader::set_vec2(const char* name, glm::vec2 vector)
	{
		glUniform2fv(get_uniform_location(name), 1, &vector[0]);
	}

	void shader::set_vec3(const char* name, float x, float y, float z)
	{
		glUniform3f(get_uniform_location(name), x, y, z);
	}

	void shader::set_vec3(const char* name, glm::vec3 vector)
	{
		glUniform3fv(get_uniform_location(name), 1, &vector[0]);
	}

	void shader::set_vec4(const char* name, glm::vec4 vector)
	{
		glUniform4fv(get_uniform_location(name), 1, &vector[0]);
	}

	void shader::set_vec4(const char* name, float x, float y, float z, float w)
	{
		glUniform4f(get_uniform_location(name), x, y, z, w);
	}

	void shader::set_mat4(const char* name, glm::mat4 const matrix)
	{
		glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
	}
}