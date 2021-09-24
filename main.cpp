#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/game.h"
#include "src/resource_manager.h"

#include <iostream>

using namespace gameModule;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

const unsigned int screenWidth = 800;
const unsigned int screenHeight = 600;

game breakout(screenWidth, screenHeight);

int main(int argc, char *argv[])
{
    if (!glfwInit())
    {
        std::cout << "Could not initialie GLFW" << std::endl;
    }

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);


    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    breakout.init();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        breakout.processInput(deltaTime);

        breakout.update(deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        breakout.render();

        glfwSwapBuffers(window);
    }

    resourceManager::clear();

    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            breakout.keys[key] = true;
        else if (action == GLFW_RELEASE)
            breakout.keys[key] = false;
            breakout.keysProcessed[key] = false;
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}