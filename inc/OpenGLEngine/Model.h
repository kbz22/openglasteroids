#pragma once

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <OpenGLEngine/Mesh.h>
#include <OpenGLEngine/TextureContainer.h>
#include <OpenGLEngine/Shader.h>

#include <vector>

namespace OpenGLEngine {

    class Model
    {
    private:
        std::vector<Mesh> m_meshes;
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
        glm::vec3 m_color;
        glm::mat4 m_modelMatrix;
        //std::vector<TextureContainer> m_loadedTextures;
        std::string m_directory;
        bool m_gammaCorrection;

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        TextureContainer loadMaterialTextures(aiMaterial* mat, std::vector<aiTextureType> types);
        void updateVectors();

    public:
        Model();
        Model(std::string_view path, bool gammaCorrection = false);

        void Draw(Shader& shader);

        void SetPos(float x, float y, float z);
        void SetRot(float pitch, float yaw, float roll);
        void Scale(float x, float y, float z);
        void Scale(float ratio);
        void SetColor(float r, float g, float b); 

        void UnitMove(float deltaTime,
            float x, float y, float z);

        glm::vec3 GetPos(void);
        glm::vec3 GetRot(void);
        glm::vec3 GetScale(void);
        glm::vec3 GetColor(void);
        glm::mat4 GetMatrix(void);

    };

}