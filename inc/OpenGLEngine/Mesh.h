#pragma once

#include <glm/glm.hpp>

#include <OpenGLEngine/TextureContainer.h>
#include <OpenGLEngine/Shader.h>

#include <vector>

namespace OpenGLEngine {

    constexpr unsigned long MaxBoneInfluence = 4;
    //constexpr unsigned long TexturesMaxAmount = 4;
    constexpr unsigned long TexturesMaxTypes = 1;

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
        int m_BoneIDs[MaxBoneInfluence];
        float m_Weights[MaxBoneInfluence];
    };

    class Mesh
    {
    public:
        std::vector<Vertex>       m_vertices;
        std::vector<unsigned int> m_indices;
        TextureContainer m_textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, TextureContainer textures);
        void Draw(Shader& shader);
    private:
        unsigned int VAO, VBO, EBO;

        void setup();
    };


}