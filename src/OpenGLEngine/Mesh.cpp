#include <OpenGLEngine/Mesh.h>

#include <glad/glad.h>

OpenGLEngine::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, TextureContainer textures)
{
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;

    setup();
}

void OpenGLEngine::Mesh::Draw(Shader& shader)
{
    unsigned int interetions = m_textures.Size() > TexturesMaxTypes ? TexturesMaxTypes : m_textures.Size();

    textureType typeList[] = { textureTypeDiffuse, textureTypeSpecular, textureTypeHeight, textureTypeNormal };
    std::map<textureType, std::vector<unsigned int>> textures;
    std::map<textureType, unsigned int> typeCount;

    for (auto type : typeList) {
        std::vector<unsigned int> getVec = m_textures.GetIDs(type);
        textures[type] = getVec;
        typeCount[type] = 0;
    }

    unsigned int i = 0;

    for (auto type : typeList)
    {
        for (auto id : textures[type]) {

            glActiveTexture(GL_TEXTURE0 + i);
            i++;

            std::string number;

            if (typeCount[type] < TexturesMaxTypes) {
                number = std::to_string(typeCount[type]++);
                shader.SetInt(("texture_diffuse" + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, id);
            }
            else break;
        }
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void OpenGLEngine::Mesh::setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
        &m_indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}
