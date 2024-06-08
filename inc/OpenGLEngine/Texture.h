#pragma once

#include <string>

namespace OpenGLEngine {

    enum textureType {
        textureTypeDiffuse = 0,
        textureTypeSpecular,
        textureTypeNormal,
        textureTypeHeight
    };

    struct Texture
    {
        unsigned int ID;
        unsigned int Width, Height;
        unsigned int InternalFormat;
        unsigned int ImageFormat;
        unsigned int WrapS;
        unsigned int WrapT;
        unsigned int FilterMin; // filtering mode if texture pixels < screen pixels
        unsigned int FilterMag; // filtering mode if texture pixels > screen pixels    
        textureType TextureType;

        Texture();
        Texture(std::string_view filepath, bool alpha = false);
        void Generate(unsigned int width, unsigned int height, unsigned char* data);
        void Bind() const;

        //friend void LoadTextureFromImage(std::string_view filepath, Texture& texture);        
    };
}