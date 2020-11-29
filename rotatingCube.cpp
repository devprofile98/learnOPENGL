#include <glad/glad.h>
#include <GLFW/glfw3.h>
//gl math
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "shader.hpp"
#include "texture.hpp"

// define vertex shader and fragment shader 

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

// setup the Camera
glm::vec3 cameraPos   = glm::vec3(7.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

int main(){
    

    // glfw init
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // glfw window creation
    // --------------------
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);
    
    // set vertex data for cube -> consist of 12 triangle or 36 float value

    float vertices[] = {

        // triangle coord       // texture cooridinate
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f


    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  -5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec4 cubesideColor[]= {
        glm::vec4(1.0f,0.0f,0.5f,1.0f),
        glm::vec4(1.0f,0.0f,0.2f,1.0f),
        glm::vec4(1.0f,0.0f,0.7f,1.0f),
        glm::vec4(1.0f,0.3f,0.5f,1.0f),
        glm::vec4(1.0f,0.1f,0.6f,1.0f),
        glm::vec4(1.0f,0.7f,0.9f,1.0f)

    };


    // create VBO and VAO : vbo for holding vertex data on gpu and VAO is used as a cache for drawing 
    uint32_t VBO,VAO;
        // generate buffer for vao
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // generate buffer for vbo
        
        glBindVertexArray(VAO);

        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);

    // set vertex attrib pointer 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(float)*5, (void*)0);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)(sizeof(float)*3));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);


    // create shader object 

    shader ourShader("../shaders/vertexshader.txt", "../shaders/fragmentshader.txt");
    uint32_t shader_link =  ourShader.createProgram();
    if (!shader_link){
        std::cout<<" ERROR OCCURED IN CREATION OF SHADER PROGRAM "<<std::endl;
        return 0;
    }

    // create texture instance -> texture will be bound inside constructor
    Texture ourTex("../shaders/side.jpg");
    Texture ourTex2("../shaders/ajor.jpg");

    // create shader program : link and compile shader's 

    ourShader.use();

    uint32_t model_index = glGetUniformLocation(ourShader.ID, "model");
    uint32_t view_index = glGetUniformLocation(ourShader.ID, "view");
    uint32_t proj_index = glGetUniformLocation(ourShader.ID, "projection");
    uint32_t color_index = glGetUniformLocation(ourShader.ID, "color");

    // glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f,0.0f,0.0f));

    glm::mat4 projection;
    projection =  glm::perspective(glm::radians(45.0f), static_cast<float>(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);

    // glUniformMatrix4fv(model_index, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(proj_index, 1, GL_FALSE, glm::value_ptr(projection));
    

    //reder loop 
    while (!glfwWindowShouldClose(window)){

        // render
        // ------
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        processInput(window);
        ourShader.use();

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f+ glfwGetTime() / 2));
        glUniformMatrix4fv(view_index, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++){

            for(unsigned int j=0; j < 20; j++)
            {
                // std::cout<<"what the fuck is going are inside here"<<std::endl;
                std::cout<< " j is "<<j<<std::endl;
                glBindTexture(GL_TEXTURE_2D, ourTex2.getID());
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[1]+glm::vec3(i,0.0,j));
                
                if ((i == 0 && j==0) || (i == 9 && j==19 ) || (i == 0 && j==19) || (i == 9 && j==0)){
                    for(int k=0;k<8;k++){
                        glBindTexture(GL_TEXTURE_2D, ourTex2.getID());
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, cubePositions[1]+glm::vec3(i,k,j));
                        glUniformMatrix4fv(model_index, 1, GL_FALSE, glm::value_ptr(model));
                        glUniform1f(color_index, (0.1f * ((i+1)%5)) + 0.1);
                        glDrawArrays(GL_TRIANGLES, 0, 6);
                        glBindTexture(GL_TEXTURE_2D, ourTex.getID());
                        glDrawArrays(GL_TRIANGLES, 6, 36);
                    }
                }

                // float angle = 20.0f * i+1; 
                // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                glUniformMatrix4fv(model_index, 1, GL_FALSE, glm::value_ptr(model));
                glUniform1f(color_index, (0.1f * ((i+1)%5)) + 0.1);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindTexture(GL_TEXTURE_2D, ourTex.getID());
                glDrawArrays(GL_TRIANGLES, 6, 36);
            }

        }

        // std::cout<< "Current frame tooks "<< deltaTime <<"ms"<<std::endl;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    float cameraSpeed = 2.5f * deltaTime;
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        cameraPos += cameraSpeed*cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}