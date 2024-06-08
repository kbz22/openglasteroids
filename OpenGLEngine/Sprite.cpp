#include <OpenGLEngine/Sprite.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void OpenGLEngine::Sprite::initRenderData()
{
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

OpenGLEngine::Sprite::Sprite(Texture &texture, glm::vec2 position, Shader &interfaceShader, glm::vec2 scale, float rotation, glm::vec3 color)
{
    //m_texture = std::make_shared<Texture>(texture);
    //m_shader = std::make_unique<Shader>(interfaceShader);
    m_texture = &texture;
    m_shader = &interfaceShader;

    m_position = position;
    m_scale = scale;
    m_color = color;
    m_rotation = rotation;

    initRenderData(); // initializes quadVAO
}

OpenGLEngine::Sprite::~Sprite()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void OpenGLEngine::Sprite::Draw(Window& window)
{
    m_shader->Use();
        
    m_shader->SetInt("image", 0);

    glm::mat4 projection = window.GetOrthoMatrix();
    m_shader->SetMat4("projection", projection);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(m_position, 0.0f));

    model = glm::translate(model, glm::vec3(m_scale.x, m_scale.y, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(m_scale.x, m_scale.y, 0.0f));

    model = glm::scale(model, glm::vec3(m_scale, 1.0f));

    m_shader->SetMat4("model", model);
    m_shader->SetVec3("spriteColor", m_color);

    glActiveTexture(GL_TEXTURE0);
    m_texture->Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

glm::vec2 OpenGLEngine::Sprite::GetScale()
{
    return m_scale;
}

void OpenGLEngine::Sprite::SetScale(glm::vec2 scale)
{
    m_scale = scale;
}

void OpenGLEngine::Sprite::SetColor(glm::vec3 color)
{
    m_color = color;
}

