
#include "Shader.h"
#include <iostream>

Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
    // Crear Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Crear Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Crear programa Shader
    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);

    // Eliminar shaders individuales
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(
        glGetUniformLocation(ID, name.c_str()),
        1,
        GL_FALSE,
        &mat[0][0]
    );
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(
        glGetUniformLocation(ID, name.c_str()),
        value
    );
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3f(
        glGetUniformLocation(ID, name.c_str()),
        value.x,
        value.y,
        value.z
    );
}
