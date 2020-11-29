#ifndef TEXTURE_H
#define TEXTURE_H

#include<iostream>
#include <stdint.h>
#include "glad/glad.h"


class Texture{
public:
    // load image, gentexture buffer, bound the texture, generate texture and it's mipmap, free the image data
    Texture(const char* texture_path);
    ~Texture();

    uint32_t getID() const;

private:
    uint32_t m_ID;

};

#endif