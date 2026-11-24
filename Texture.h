
#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
public:

    GLuint ID;

    Texture(const char* imagePath);

    Texture(const unsigned char* data, int width, int height, int channels);

    void bind(GLuint slot = 0) const;

    void cleanup();
};
