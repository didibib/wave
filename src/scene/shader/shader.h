#pragma once

namespace Wave
{
	class Shader
	{
	public:
		Shader();
		~Shader();
		bool Load(std::string const& filename);
		void Begin();
		void End();

		GLuint GetUniformLocation(std::string const& name);
		void SetInt(const char* name, int const& value);
		void SetFloat(const char* name, float const& value);
		void SetVec2(const char* name, glm::vec2 const& vector);
		void SetVec2(const char* name, float const& x, float const& y);
		void SetVec3(const char* name, glm::vec3 const& vector);
		void SetVec3(const char* name, float const& x, float const& y, float const& z);
		void SetVec4(const char* name, glm::vec4 const& vector);
		void SetVec4(const char* name, float const& x, float const& y, float const& z, float const& w);
		void SetMat4(const char* name, glm::mat4 const& matrix);

	private:
		GLuint CompileShader(GLenum shader_type, std::string const& file);
		void LinkShader(GLuint& vert_id, GLuint& frag_id);

		GLuint m_ProgramId;
	};
}