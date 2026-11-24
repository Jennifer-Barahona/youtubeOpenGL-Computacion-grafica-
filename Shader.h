
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:

    GLuint ID;

    Shader(const char* vertexSource, const char* fragmentSource);

    void use() const;

    void setMat4(const std::string& name, const glm::mat4& mat) const;

    void setInt(const std::string& name, int value) const;

    void setVec3(const std::string& name, const glm::vec3& value) const;
};
