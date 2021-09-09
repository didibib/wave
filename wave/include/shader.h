#pragma once

namespace wave
{
	class shader
	{
	public:
		shader();
		~shader();
		bool load(const std::string filename);
		void begin();
		void end();;

		GLuint get_uniform_location(const std::string name);
		void set_int(const char* name, const int value);
		void set_float(const char* name, const float value);
		void set_vec2(const char* name, glm::vec2 vector);
		void set_vec2(const char* name, float x, float y);
		void set_vec3(const char* name, glm::vec3 vector);
		void set_vec3(const char* name, float x, float y, float z);
		void set_vec4(const char* name, glm::vec4 vector);
		void set_vec4(const char* name, float x, float y, float z, float w);
		void set_mat4(const char* name, glm::mat4 const matrix);

	private:
		GLuint compile_shader(GLenum shader_type, const std::string& file);
		void link_shader(GLuint& vert_id, GLuint& frag_id);

		GLuint m_program_id;
	};
}