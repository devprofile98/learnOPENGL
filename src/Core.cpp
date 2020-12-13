#include "Core.hpp"


// constructor
Engine::Engine()
{

    m_width = 1080;
    m_height= 1080;

    // glfw init
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // glfw window creation
    // --------------------
        window = glfwCreateWindow(m_width, m_height, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }

        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);


        glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

Engine::~Engine(){

    delete m_shader_program;
    delete m_texture1;
    delete m_texture2;
}


bool Engine::start(const char* vshader_path, const char* fshader_path ,const char* texture_path)
{
    // generate buffer for vao
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // generate buffer for vbo
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices.front(),GL_STATIC_DRAW);

    // set vertex attrib pointer 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(float)*5, (void*)0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)(sizeof(float)*3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    // create shader object 
    
    m_shader_program = new shader(
        vshader_path ? vshader_path : "../shaders/vertexshader.txt",
        fshader_path ? fshader_path : "../shaders/fragmentshader.txt"
         );
    uint32_t shader_link =  m_shader_program->createProgram();
    if (!shader_link){
        std::cout<<" ERROR OCCURED IN CREATION OF SHADER PROGRAM "<<std::endl;
        return false;
    }

    // create texture instance -> texture will be bound inside constructor
    m_texture1 = new Texture("../shaders/side.jpg");
    m_texture2 = new Texture("../shaders/minecraft-person1-face.jpg");

    m_shader_program->use();
    model_location = glGetUniformLocation(m_shader_program->ID, "model");
    view_location = glGetUniformLocation(m_shader_program->ID, "view");
    projection_location = glGetUniformLocation(m_shader_program->ID, "projection");

    projection =  glm::perspective(glm::radians(45.0f), static_cast<float>(m_width / m_height), 0.1f, 100.0f);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

    return true;
}


void Engine::run(){

}

void Engine::processInput()
{
    float cameraSpeed = 2.5f * deltaTime ;
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        Engine::cameraPos += cameraSpeed*Engine::cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Engine::cameraPos -= cameraSpeed * Engine::cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Engine::cameraPos -= glm::normalize(glm::cross(Engine::cameraFront, Engine::cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Engine::cameraPos += glm::normalize(glm::cross(Engine::cameraFront, Engine::cameraUp)) * cameraSpeed;

}

int Engine::Width()
{
    return m_width;
}

int Engine::Height(){

    return m_height;
}


glm::vec3 Engine::cameraPos   = glm::vec3(0.0f, 0.0f,  10.0f);
glm::vec3 Engine::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Engine::cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);