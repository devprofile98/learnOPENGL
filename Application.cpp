#include "Core.hpp"


class Application:public Engine{

public:
    Application():Engine(){};
    ~Application();

void run(){
        
    m_shader_program->use();
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
    glBindVertexArray(VAO);

    // Drawing 
    for(int i=0;i<10;i++){
        glBindTexture(GL_TEXTURE_2D, m_texture2->getID());
        glm::mat4 model = glm::mat4(1.0f);
        // std::cout<<i<< " "<<cubePositions[i].x<<" "<<cubePositions[i].y<<" "<<cubePositions[i].z<<std::endl;
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0,0.0,1.0));
        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
        // glUniform1f(color_index, (0.1f * ((i+1)%5)) + 0.1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindTexture(GL_TEXTURE_2D, m_texture1->getID());
        glDrawArrays(GL_TRIANGLES, 6, 36);
    }
    // End of drawing


        glfwSwapBuffers(window);
        glfwPollEvents();

}

private:

};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


int main(){

    Application *app = new Application{};
    app->start();
    float r,g,b;
    r = (float)135 / 255;
    g = (float)80 / 255;
    b = (float)199 / 255;
    while (true)
    {
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        float currentFrame = glfwGetTime();
        app->deltaTime = currentFrame - app->lastFrame;
        app->lastFrame = currentFrame;        
        app->processInput();
        app->run();

    }
    
    delete app;
    return 0;
}