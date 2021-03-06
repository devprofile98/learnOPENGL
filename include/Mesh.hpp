#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <stdint.h>
#include <vector>
#include "shader.hpp"

// Struct container for single Vertex information
struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
        // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;

};

// Struct container for Texture information 
// id : unique texture unit id
// type : type of Texture -> diffuse or specular map texture 
struct Texture{
    uint32_t id;
    std::string type;
    std::string path;
};


class Mesh{
public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture> textures;
    
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);
    void Draw(shader &shader);

private:
    //  render data
    uint32_t VAO, VBO, EBO;

    void setupMesh();

};



#endif //ENGINE_MESH_H