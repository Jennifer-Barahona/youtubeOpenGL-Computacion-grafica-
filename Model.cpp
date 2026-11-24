
#include "Model.h"
#include "stb_image.h"

#include <iostream>
#include <vector>

Model::Model(const char* path)
{
    loadModel(path);
}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_GenSmoothNormals
    );

    if (!scene || !scene->mRootNode ||
        (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE))
    {
        std::cout << "Error al cargar modelo: "
            << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of("/\\"));

    processNode(scene->mRootNode, scene);

    std::cout << "Modelo cargado correctamente" << std::endl;
    std::cout << "Cantidad de mallas: " << meshes.size() << std::endl;
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Posicion, normales y coordenadas UV
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        // Posicion
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        // Normales
        if (mesh->HasNormals())
        {
            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);
        }
        else
        {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }

        // Coordenadas UV
        if (mesh->mTextureCoords[0])
        {
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }
        else
        {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    // Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Materiales y texturas
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // Textura de color base
        std::vector<Texture> baseColorTextures =
            loadMaterialTextures(
                material,
                aiTextureType_BASE_COLOR,
                "texture_diffuse",
                scene
            );

        textures.insert(
            textures.end(),
            baseColorTextures.begin(),
            baseColorTextures.end()
        );

        // Textura difusa como alternativa
        if (textures.empty())
        {
            std::vector<Texture> diffuseTextures =
                loadMaterialTextures(
                    material,
                    aiTextureType_DIFFUSE,
                    "texture_diffuse",
                    scene
                );

            textures.insert(
                textures.end(),
                diffuseTextures.begin(),
                diffuseTextures.end()
            );
        }
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(
    aiMaterial* mat,
    aiTextureType type,
    const std::string& typeName,
    const aiScene* scene)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;

        if (mat->GetTexture(type, i, &str) != AI_SUCCESS)
            continue;

        const aiTexture* embeddedTexture =
            scene->GetEmbeddedTexture(str.C_Str());

        // TEXTURA INCRUSTADA EN EL GLB
        if (embeddedTexture)
        {
            // Imagen comprimida: PNG, JPEG, etc.
            if (embeddedTexture->mHeight == 0)
            {
                int width, height, channels;

                unsigned char* data = stbi_load_from_memory(
                    reinterpret_cast<const unsigned char*>(
                        embeddedTexture->pcData
                        ),
                    static_cast<int>(embeddedTexture->mWidth),
                    &width,
                    &height,
                    &channels,
                    0
                );

                if (data)
                {
                    textures.emplace_back(
                        data, width, height, channels
                    );

                    stbi_image_free(data);

                    std::cout << "Textura incrustada cargada"
                        << std::endl;
                }
                else
                {
                    std::cout << "Error al decodificar textura incrustada"
                        << std::endl;
                }
            }
            // Imagen sin comprimir
            else
            {
                std::vector<unsigned char> pixels;

                for (unsigned int j = 0;
                    j < embeddedTexture->mWidth * embeddedTexture->mHeight;
                    j++)
                {
                    const aiTexel& texel = embeddedTexture->pcData[j];

                    pixels.push_back(texel.r);
                    pixels.push_back(texel.g);
                    pixels.push_back(texel.b);
                    pixels.push_back(texel.a);
                }

                textures.emplace_back(
                    pixels.data(),
                    embeddedTexture->mWidth,
                    embeddedTexture->mHeight,
                    4
                );

                std::cout << "Textura sin compresion cargada"
                    << std::endl;
            }
        }
        // TEXTURA EXTERNA
        else
        {
            std::string filename = str.C_Str();

            if (filename.find('/') == std::string::npos &&
                filename.find('\\') == std::string::npos)
            {
                filename = directory + "/" + filename;
            }

            Texture texture(filename.c_str());

            textures.push_back(texture);
        }
    }

    return textures;
}

void Model::draw() const
{
    for (const Mesh& mesh : meshes)
    {
        mesh.draw();
    }
}
