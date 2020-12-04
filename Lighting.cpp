#include "Core.hpp"


float aspectRatio = 0;


class Application : public Engine{
public:
    Application():Engine(){};
    ~Application(){};

    void run(){
        
    m_shader_program->use();
    glm::mat4 view = glm::mat4(1.0f);

    uint32_t viewPos = glGetUniformLocation(m_shader_program->ID, "viewPos");
    glUniform3fv(viewPos,1,glm::value_ptr(cameraPos));

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
    glBindVertexArray(VAO);

    // Drawing 
for(int i=0;i<5;i++){
    // glBindTexture(GL_TEXTURE_2D, m_texture2->getID());
    glm::mat4 model = glm::mat4(1.0f);
    // std::cout<<i<< " "<<cubePositions[i].x<<" "<<cubePositions[i].y<<" "<<cubePositions[i].z<<std::endl;
    model = glm::translate(model, cubePositions[i]);
    // model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0,0.0,1.0));
    model = glm::scale(model, glm::vec3(aspectRatio, 1.0f, 1.0f));
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
    // glUniform1f(color_index, (0.1f * ((i+1)%5)) + 0.1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // glBindTexture(GL_TEXTURE_2D, m_texture1->getID());`
    glDrawArrays(GL_TRIANGLES, 6, 36);
}
// End of drawing


    glfwSwapBuffers(window);
    glfwPollEvents();
    

}

    void config() {
        std::cout<<"overrided function is here"<<std::endl;
        uint32_t lightVAO;
        glGenBuffers(1, &lightVAO);
        glBindVertexArray(lightVAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0*sizeof(float)));
        glEnableVertexAttribArray(0);

        m_shader_program->use();
        uint32_t objColor,lightColor;
        objColor = glGetUniformLocation(m_shader_program->ID, "objectColor");
        lightColor= glGetUniformLocation(m_shader_program->ID, "lightColor");

        glUniform3fv(objColor,1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
        glUniform3fv(lightColor,1, glm::value_ptr(glm::vec3(1.0f)));


    }

    bool start(const char* vshader_path, const char* fshader_path ,const char* texture_path)
    {

        std::cout<<"DAYI GOLOO HA MAN INJA HASTAM\n\n\n\n\n\n"<<std::endl;
        std::cout<<"DAYI GOLOO HA MAN INJA HASTAM"<<std::endl;
        // generate buffer for vao
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // generate buffer for vbo
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices.front(),GL_STATIC_DRAW);

        // set vertex attrib pointer 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(float)*6, (void*)0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,(void*)(sizeof(float)*3));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

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
        uint32_t light_location;
        light_location = glGetUniformLocation(m_shader_program->ID, "lightPos");
        glUniform3fv(light_location, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 5.0f)));

        projection =  glm::perspective(glm::radians(45.0f), static_cast<float>(m_width / m_height), 0.1f, 100.0f);
        glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

        return true;

    }
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    aspectRatio = (float)height/width ;
    glViewport(0, 0, width, height);
}


int main(){

    Application *app = new Application{};
    app->start(nullptr,"../shaders/lightingFragmentShader.txt",nullptr);
    app->config();
    aspectRatio = (float)app->Width() / app->Height();

    shader lightshader("../shaders/vertexshader.txt","../shaders/lightsourceFragment.txt");
    lightshader.createProgram();
    lightshader.use();
    uint32_t model_l,view_l,projection_l;
    model_l = glGetUniformLocation(lightshader.ID,"model");
    view_l = glGetUniformLocation(lightshader.ID,"view");
    projection_l = glGetUniformLocation(lightshader.ID,"projection");
    std::cout<<" light shader unifrom locations are "<<model_l<<view_l<<projection_l<<std::endl;
    glm::mat4 projection =  glm::perspective(glm::radians(45.0f), static_cast<float>(app->Width()/ app->Height()), 0.1f, 100.0f);
    glUniformMatrix4fv(projection_l, 1, GL_FALSE, glm::value_ptr(projection));

    // glUniformMatrix4fv(projection_l,1,GL_FALSE,glm::value_ptr(projection));
    
    glm::mat4 view = glm::mat4(1.0f);

    glm::vec3 lightPos(1.0f, 0.5f, 5.0f);       



    float r,g,b;
    r = (float)90 / 255;
    g = (float)80 / 255;
    b = (float)199 / 255;
    

    while (!glfwWindowShouldClose(app->window))
    {
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        float currentFrame = glfwGetTime();
        app->deltaTime = currentFrame - app->lastFrame;
        app->lastFrame = currentFrame;        
        app->processInput();    

        view = glm::lookAt(app->cameraPos, app->cameraPos + app->cameraFront, app->cameraUp);
        lightshader.use();
        glUniformMatrix4fv(view_l,1,GL_FALSE,glm::value_ptr(view));
        glm::mat4 model = glm::mat4(1.0f);
        // std::cout<<i<< " "<<cubePositions[i].x<<" "<<cubePositions[i].y<<" "<<cubePositions[i].z<<std::endl;
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(aspectRatio/5,1.0f/5, 1.0f/5));
        glUniformMatrix4fv(model_l,1,GL_FALSE,glm::value_ptr(model));
        
        glDrawArrays(GL_TRIANGLES,0,36);

        app->run();

    }
    
    delete app;
    return 0;
}