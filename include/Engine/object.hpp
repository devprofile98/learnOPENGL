#ifndef ENGNE_OBJECT_H
#define ENGNE_OBJECT_H


#include <stdint.h>
#include <memory>
#include "../shader.hpp"
#include "../texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #include "cubeVertices.hpp"


//abstract class for every visual object in scene
class object {

public:

    object(); // default constructor  
    virtual ~object();

    object(const object& other); // copy constructor
    
    virtual void setShaderProgram(const char* vertexSahderPath=nullptr, const char* fragmentShaderPath=nullptr); // create a shader program and set m_shader_program 
    virtual uint32_t getShaderProgramID() const ; // return the m_shader_program->ID
    virtual shader* getShader() const; // return this->m_shader_program

    virtual void setTexture(const char* texture_image_path=nullptr, uint8_t layout_location=0); // set the texture
    // virtual uint32_t getTextureID() const; // return texture->ID
    virtual Texture* getTexture() const; // return this->m_texture

    virtual void setPosition(const glm::vec3& pos);
    virtual glm::vec3 getPosition() const;


private:
    shader*     m_shader_program;  
    Texture*    m_texture;
    glm::vec3   m_position{0.0f};
    
    /*
    lightmap m_lightmap;
    */
    
};



#endif // ENGNE_OBJECT_H