#include <glad/glad.h>
#include <GLFW/glfw3.h>
//gl math
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;


const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location=0) in vec3 aPos;\n"
                                 "layout (location=1) in vec4 aColor;\n"
                                 "out vec4 outColor;\n"
                                 "uniform mat4 transform;\n"
                                 " void main() {\n"
                                 "outColor = aColor;\n"
                                 "gl_Position = transform * vec4(aPos,1.0);}\n"
        ;


const char *fragmentShaderSource = "#version 330 core\n"
                                   "in vec4 outColor;\n"
                                   "out vec4 FragColor;\n"
                                   "void main(){\n"
                                   "FragColor = outColor;}\n";



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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


    float vertecis[] = {
        -0.25f,-0.25f, 0.0f, 1.0f,1.0f,0.5f,1.0f,// left
        0.25f, -0.25f, 0.0f, 1.0f,0.4f,0.5f,1.0f,// right
        0.25f,  0.25f, 0.0f, 1.0f,0.4f,0.5f,1.0f,// top right
        -0.25f, 0.25f, 0.0f, 1.0f,0.4f,0.5f,1.0f,//top left

        // top parallelorgam // bottom left is 3 // bottom right is 2
        -0.12f, 0.37f, 0.0f,   1.0f,0.4f,0.5f,1.0f,  // top left
        0.37f, 0.37f, 0.0f,    1.0f,0.4f,0.9f,1.0f, //top right

        // side rectangle 3-point is available from top
        0.37f, -0.12f, 0.0f,   1.0f,0.4f,0.5f,1.0f// bottom right point

    };

    float colors[] = {
        1.0f,0.4f,0.5f,1.0f // color for first rectangle
    };


    uint32_t indices[] = {
        0,1,2,   // left triangle
        0,3,2,    // second triangle

        4,3,2,    // bottom half-parallelorgam
        5,4,2,     // top half-parallelorgam

        5,2,1,      // left half of side rectanlge
        5,6,1       // right half of side rectangle

    };

    uint32_t VBO, VAO, EBO;

    glGenBuffers(1,&EBO);

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertecis),vertecis,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    uint32_t vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
    glCompileShader(vertexShader);


    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,nullptr,infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED"<<std::endl;
        std::cout<<infoLog<<std::endl;
    }


    uint32_t fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,nullptr,infoLog);
        std::cout<<"ERROR::SHADER::FragMENT::COMPILATION_FAILED"<<std::endl;
        std::cout<<infoLog<<std::endl;
    }


    uint32_t shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,nullptr,infoLog);
        std::cout<<"ERROR::PROGRAM::LINKING::FAILED"<<std::endl;
        std::cout<<infoLog<<std::endl;
    }


    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.6, 0.6, 0.6));

    glUseProgram(shaderProgram);
//    int fragColor = glGetUniformLocation(shaderProgram, "fragColor");
//    glUniform3fv(fragColor,1,glm::value_ptr(glm::vec3(0.3f,0.6f,0.9f)));
    int index = glGetUniformLocation(shaderProgram,"transform");
    std::cout<<"the shader id is "<<shaderProgram<< " " << index;
    glUniformMatrix4fv(index, 1, GL_FALSE, glm::value_ptr(trans));
//    glUniform1f(index,12.0f);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 7 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);


    int scale = 0;
    bool scale_side = false;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(1/2.0f,static_cast<float>(1920.0/1080.0)/2.0f,1/2.0f));
        trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
        glUniformMatrix4fv(index, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
