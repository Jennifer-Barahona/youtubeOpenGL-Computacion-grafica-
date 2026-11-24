
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model {
public:

    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;

    std::string directory;

    Model(const char* path);

    void draw() const;

private:

    void loadModel(const std::string& path);

    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Texture> loadMaterialTextures(
        aiMaterial* mat,
        aiTextureType type,
        const std::string& typeName,
        const aiScene* scene
    );
};

