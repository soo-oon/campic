#pragma once

#include <GL\glew.h>
#include <string>
#include <map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>

class Shader
{
public:
	Shader() = default;
	Shader& Use();

	void Delete();

	bool Compile(const std::string& vertex_scr,
		const std::string& fragment_src);

	void SendUniformVariable(const std::string& name, GLfloat value);

	void SendUniformVariable(const std::string& name, GLint value);

	void SendUniformVariable(const std::string& name, glm::vec2 vector);

	void SendUniformVariable(const std::string& name, glm::vec3 vector);

	void SendUniformVariable(const std::string& name, const glm::mat3& affine_matrix);

	void SendUniformVariable(const std::string& name, const Color color);

	int GetVertexAttributeLocation(const std::string& vertex_field_name) const;

	GLuint GetShaderHandler() const { return handle_to_shader; }

private:
	std::map<std::string, int> uniformNameToLocation{};

private:
	void Compile_Check(GLuint object, std::string type);
	GLuint handle_to_shader;

};