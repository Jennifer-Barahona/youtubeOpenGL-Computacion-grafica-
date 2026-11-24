

#include "Mesh.h"

Mesh::Mesh(
    const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices,
    const std::vector<Texture>& textures
)
{
    this->textures = textures;

    indexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Enviar vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    // Enviar indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );

    // Cada vertice tiene 8 valores
    GLsizei stride = 8 * sizeof(float);

    // Posicion
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        stride, (void*)0
    );
    glEnableVertexAttribArray(0);

    // Normales
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        stride, (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    // Coordenadas de textura
    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE,
        stride, (void*)(6 * sizeof(float))
    );
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::draw() const
{
    // Activar las texturas de la malla
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        textures[i].bind(i);
    }

    glBindVertexArray(VAO);

    glDrawElements(
        GL_TRIANGLES,
        indexCount,
        GL_UNSIGNED_INT,
        0
    );

    glBindVertexArray(0);
}

void Mesh::cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
