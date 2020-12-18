#include "object.hpp"

object::object(){}

object::~object(){
    // free resources
    delete m_shader_program;
    delete m_texture;
}

object::object(const object& other){
    // deep copy
    this->m_shader_program = other.m_shader_program;
    this->m_texture = other.m_texture;
}

// code for creating and managing shaders
//create default fragment and vertex shader if value == nullptr
void object::setShaderProgram(const char* vshaderpath, const char* fshaderpath){
    
    m_shader_program = new shader(
        vshaderpath ? vshaderpath : "../shaders/vertexshader.txt",
        fshaderpath ? fshaderpath : "../shaders/fragmentshader.txt"
    );

    //TODO must implement a callback shader setter
    if(!m_shader_program->createProgram()){
        std::cout<<"ENGINE::OBJECT::SET_SHADER::ERROR:: can't create shader program"<<std::endl;
        return;
    }
}

// return shaderprogram ID
uint32_t object::getShaderProgramID() const {
    return m_shader_program->ID;
}

// return entire shader object
shader* object::getShader() const {
    return m_shader_program;
}


// code for creating and managing textures

void object::setTexture(const char* texture_image_path,uint8_t layout_location){
    m_texture = new Texture(texture_image_path);
    std::cout<<"object Texture created with id: "<<m_texture->getID()<<std::endl;
}

Texture* object::getTexture() const{
    return m_texture;
}

void object::setPosition(const glm::vec3& pos){
    m_position = pos;
}

glm::vec3 object::getPosition() const {
    return m_position;
}
