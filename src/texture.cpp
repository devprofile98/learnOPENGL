#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* texture_path, uint32_t layout_location){

    int width, height,channel;
    unsigned char* data = stbi_load(texture_path, &width,&height,&channel,0);
    m_ID = layout_location;
    glGenTextures(1, &m_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, m_ID);
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB,GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    
    }
    else{
        std::cout<<" Failed to load texture from source "<<std::endl;
    }

    stbi_image_free(data);

}

Texture::~Texture(){
        std::cout<<" TEXTURE WITH ID: "<<m_ID <<" DESTROYED!"<<std::endl;
}

uint32_t Texture::getID() const {
    return m_ID;
}

