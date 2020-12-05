#ifndef SHADER_H
#define SHADER_H


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

        void setVec3(const char* uniform_name,glm::vec3 &value) const ;
        void setVec3(const char* uniform_name,float x, float y, float z) const ;

        void setFloat(const char* uniform_name, float value) const ;



    private:

        std::string vShaderCode;
        std::string fShaderCode;   

        uint32_t m_vertex, m_fragment; // fragment shader and vertex shader id
        


};


#endif