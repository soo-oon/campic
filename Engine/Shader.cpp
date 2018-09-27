#include <iostream>
#include "Color.hpp"
#include "Shader.hpp"

Shader & Shader::Use()
{
	glUseProgram(handle_to_shader);
	return *this;
}

void Shader::Delete()
{
    if(handle_to_shader)
    {
        glDeleteProgram(handle_to_shader);
    }

    handle_to_shader = 0;
}

bool Shader::Compile(const std::string & vertex_scr, const std::string & fragment_src)
{
	GLuint Vertex, Fragment;

	// vertex shader
	Vertex = glCreateShader(GL_VERTEX_SHADER);
	const char *c_str = vertex_scr.c_str();
	glShaderSource(Vertex, 1, &c_str, NULL);
	glCompileShader(Vertex);
	Compile_Check(Vertex, "VERTEX");

	// fragment shader
	Fragment = glCreateShader(GL_FRAGMENT_SHADER);
	c_str = fragment_src.c_str();
	glShaderSource(Fragment, 1, &c_str, NULL);
	glCompileShader(Fragment);
	Compile_Check(Fragment, "FRAGMENT");

	// shader program
	handle_to_shader = glCreateProgram();
	glAttachShader(handle_to_shader, Vertex);
	glAttachShader(handle_to_shader, Fragment);

	glLinkProgram(handle_to_shader);
	Compile_Check(handle_to_shader, "PROGRAM");

	glDeleteShader(Vertex);
	glDeleteShader(Fragment);

	return handle_to_shader != 0;
}

void Shader::SendUniformVariable(const std::string & name, GLfloat value)
{
    Use();

    glUniform1f(glGetUniformLocation(handle_to_shader, name.c_str()), value);
}

void Shader::SendUniformVariable(const std::string & name, GLint value)
{
    Use();

    glUniform1i(glGetUniformLocation(handle_to_shader, name.c_str()), value);
}

void Shader::SendUniformVariable(const std::string & name, vector2 vector)
{
    Use();

    glUniform2fv(glGetUniformLocation(handle_to_shader, name.c_str()),1, &vector.x);
}

void Shader::SendUniformVariable(const std::string & name, vector3 vector)
{
    Use();

    glUniform3fv(glGetUniformLocation(handle_to_shader, name.c_str()), 1, &vector.x);
}

void Shader::SendUniformVariable(const std::string & name, const affine2d & affine_matrix)
{
    Use();

    glUniformMatrix3fv(glGetUniformLocation(handle_to_shader, name.c_str()), 1, GL_TRUE,&affine_matrix.affine[0][0]);
}

void Shader::SendUniformVariable(const std::string & name, const Color color)
{
    Use();

    auto vec4 = color.RGBAfloat();

    glUniform4fv(glGetUniformLocation(handle_to_shader, name.c_str()), 1, &vec4.x);

}

int Shader::GetVertexAttributeLocation(const std::string& vertex_field_name) const
{
    auto attriblocation = glGetAttribLocation(handle_to_shader, vertex_field_name.c_str());

    return attriblocation;
}

void Shader::Compile_Check(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}
