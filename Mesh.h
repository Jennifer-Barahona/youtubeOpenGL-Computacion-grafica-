
#pragma once

#include <glad/glad.h>
#include <vector>

#include "Texture.h"

class Mesh {
public:

    GLuint VAO, VBO, EBO;

    GLsizei indexCount;

    std::vector<Texture> textures;

    Mesh(
        const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices,
        const std::vector<Texture>& textures
    );

    void draw() const;

    void cleanup();
};
