#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>


class shader{

    public:
        shader(const char* vertexPath, const char* fragmentPath);
        ~shader();


        bool createProgram();
        void use();
        uint16_t ID;    // shader program id

    private:

        std::string vShaderCode;
        std::string fShaderCode;   

        uint32_t m_vertex, m_fragment; // fragment shader and vertex shader id
        


};


#endif