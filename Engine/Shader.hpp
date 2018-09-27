#pragma once

#include <GL\glew.h>
#include <string>
#include <map>
#include "vector2.hpp"
#include "vector3.hpp"
#include "affine2d.hpp"

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

	void SendUniformVariable(const std::string& name, vector2 vector);

	void SendUniformVariable(const std::string& name, vector3 vector);

	void SendUniformVariable(const std::string& name, const affine2d& affine_matrix);

	void SendUniformVariable(const std::string& name, const Color color);

	int GetVertexAttributeLocation(const std::string& vertex_field_name) const;

	GLuint GetShaderHandler() const { return handle_to_shader; }

private:
	std::map<std::string, int> uniformNameToLocation{};

private:
	void Compile_Check(GLuint object, std::string type);
	GLuint handle_to_shader;

};