#include <OpenGLEngine/Texture.h>

#include <glad/glad.h>
#include <stb/stb_image.h>

OpenGLEngine::Texture::Texture() 
    : Width(0), Height(0), InternalFormat(GL_RGB), ImageFormat(GL_RGB), WrapS(GL_REPEAT), WrapT(GL_REPEAT), FilterMin(GL_LINEAR), FilterMag(GL_LINEAR), TextureType(textureTypeDiffuse)
{
    glGenTextures(1, &this->ID);
}

OpenGLEngine::Texture::Texture(std::string_view filepath, bool alpha)
    : Texture()
{
    if (filepath.empty())
        return;

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filepath.data(), &width, &height, &nrComponents, 0);

    if (!data) throw std::exception("texture image load error");

    switch (nrComponents) {
    case 1:
        this->InternalFormat = GL_RED;
        this->ImageFormat = GL_RED;
        break;
    default:
    case 3:
        this->InternalFormat = GL_RGB;
        this->ImageFormat = GL_RGB;
        break;
    case 4:
        this->InternalFormat = GL_RGBA;
        this->ImageFormat = GL_RGBA;
        break;
    }

    this->Generate(width, height, data);

    stbi_image_free(data);

    return;
}

void OpenGLEngine::Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->Width = width;
    this->Height = height;

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->InternalFormat, width, height, 0, this->ImageFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->WrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->FilterMag);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLEngine::Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}