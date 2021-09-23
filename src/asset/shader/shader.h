#pragma once

namespace Wave
{
	class Shader
	{
	public:
		Shader();
		~Shader();
		bool Load(const std::string filename);
		void Begin();
		void End();;

		GLuint GetUniformLocation(const std::string name);
		void SetInt(const char* name, const int value);
		void SetFloat(const char* name, const float value);
		void SetVec2(const char* name, glm::vec2 vector);
		void SetVec2(const char* name, float x, float y);
		void SetVec3(const char* name, glm::vec3 vector);
		void SetVec3(const char* name, float x, float y, float z);
		void SetVec4(const char* name, glm::vec4 vector);
		void SetVec4(const char* name, float x, float y, float z, float w);
		void SetMat4(const char* name, glm::mat4 const matrix);

	private:
		GLuint CompileShader(GLenum shader_type, const std::string& file);
		void LinkShader(GLuint& vert_id, GLuint& frag_id);

		GLuint m_ProgramId;
	};
}