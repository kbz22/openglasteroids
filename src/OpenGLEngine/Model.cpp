#include <OpenGLEngine/Model.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void OpenGLEngine::Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::string err_msg = "model loading error: ";
        err_msg.append(importer.GetErrorString()).append("\n");
        throw std::exception(err_msg.c_str());
    }
    m_directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void OpenGLEngine::Model::processNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

OpenGLEngine::Mesh OpenGLEngine::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            if (mesh->mTangents) {
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
            }

            // bitangent
            if (mesh->mBitangents) {
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            }
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // 1. diffuse maps
    std::vector<aiTextureType> types = { aiTextureType_DIFFUSE , aiTextureType_SPECULAR, aiTextureType_HEIGHT, aiTextureType_AMBIENT };
    TextureContainer texts = loadMaterialTextures(material, types);

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, texts);
}

OpenGLEngine::textureType TranslateType(aiTextureType type) {
    switch (type) {
    case aiTextureType_DIFFUSE:
        return OpenGLEngine::textureTypeDiffuse;
    case aiTextureType_SPECULAR:
        return OpenGLEngine::textureTypeSpecular;
    case aiTextureType_HEIGHT:
        return OpenGLEngine::textureTypeNormal;
    case aiTextureType_AMBIENT:
        return OpenGLEngine::textureTypeHeight;
    }
}

OpenGLEngine::TextureContainer OpenGLEngine::Model::loadMaterialTextures(aiMaterial* mat, std::vector<aiTextureType> types)
{
    std::map<std::string, OpenGLEngine::textureType> filenames;

    for (auto type : types) {
        if (mat->GetTextureCount(type) == 0) {
            continue;
        }

        aiString str;
        mat->GetTexture(type, 0, &str);

        filenames[str.C_Str()] = TranslateType(type);
    }

    return TextureContainer(filenames);
}

void OpenGLEngine::Model::updateVectors()
{
    /*
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, GetPos());
    model = glm::rotate(model, glm::radians(GetRot().x), glm::vec3(0, 0, 1));
    model = glm::rotate(model, glm::radians(GetRot().y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(GetRot().z), glm::vec3(1, 0, 0));    
    model = glm::scale(model, GetScale());

    m_modelMatrix = model;
    */
}

OpenGLEngine::Model::Model() {}

OpenGLEngine::Model::Model(std::string_view path, bool gammaCorrection) : m_gammaCorrection(gammaCorrection)
{
    try {
        loadModel(path.data());
    }
    catch (std::exception e) {
        throw e;
    }
    m_position.x = 0;
    m_position.y = 0;
    m_position.z = 0;
    m_scale.x = 1;
    m_scale.y = 1;
    m_scale.z = 1;
    m_color.r = 1;
    m_color.g = 1;
    m_color.b = 1;
    updateVectors();
}

void OpenGLEngine::Model::Draw(Shader& shader)
{    
    for (auto mesh : m_meshes)
        mesh.Draw(shader);
}

void OpenGLEngine::Model::SetPos(float x, float y, float z)
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;

    updateVectors();
}

void OpenGLEngine::Model::SetRot(float pitch, float yaw, float roll)
{
    m_rotation.x = pitch;
    m_rotation.y = yaw;
    m_rotation.z = roll;

    updateVectors();
}

glm::vec3 OpenGLEngine::Model::GetPos(void)
{
    return m_position;
}

glm::vec3 OpenGLEngine::Model::GetRot(void)
{
    return m_rotation;
}

void OpenGLEngine::Model::SetColor(float r, float g, float b)
{
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;

    updateVectors();
}

void OpenGLEngine::Model::UnitMove(float deltaTime, float x, float y, float z)
{
    glm::vec3 unitMovement(x * deltaTime,y * deltaTime,z * deltaTime);        

    m_position += unitMovement;    

    updateVectors();
}

glm::vec3 OpenGLEngine::Model::GetScale(void)
{
    return m_scale;
}

glm::vec3 OpenGLEngine::Model::GetColor(void) {
    return m_color;
}

glm::mat4 OpenGLEngine::Model::GetMatrix(void)
{
 //   return m_modelMatrix;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(0, 0, 1));
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(1, 0, 0));
    model = glm::scale(model, m_scale);

    return model;
}

void OpenGLEngine::Model::Scale(float x, float y, float z)
{
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;

    updateVectors();
}

void OpenGLEngine::Model::Scale(float ratio)
{
    m_scale.x = ratio;
    m_scale.y = ratio;
    m_scale.z = ratio;

    updateVectors();
}

