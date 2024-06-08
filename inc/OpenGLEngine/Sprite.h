#pragma once

#include <glm/glm.hpp>

#include <OpenGLEngine/Texture.h>
#include <OpenGLEngine/Shader.h>
#include <OpenGLEngine/Window.h>

#include <memory>

namespace OpenGLEngine {

    class Sprite
    {
    private:
        Texture* m_texture;
        Shader* m_shader;
        glm::vec2 m_scale;
        glm::vec2 m_position;
        float m_rotation;
        glm::vec3 m_color;

        unsigned int quadVAO;

        void initRenderData();

    public:
        Sprite(Texture &texture,
            glm::vec2 position,
            Shader &interfaceShader,
            glm::vec2 scale = glm::vec2(1.0f, 1.0f),
            float rotation = 0.0f,
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
        ~Sprite();

        void Draw(Window &window);  

        glm::vec2 GetScale();

        void SetScale(glm::vec2 scale);
        void SetColor(glm::vec3 color);
    };

}