#include <iostream>
// #include <glad/glad.h>
#include "api/Api.h"

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;
const std::string TITLE = "GLFW Window";
const bool FULLSCREEN = false;

int main() {
    try {
        glfwInit();

        Window engine;

        engine.ContextCurrent();

       Shader shader;

        std::string text = shader.ReadShaderFromFile("vertex.vert");
        std::cout << text << std::endl;

        engine.loop();
        return 0;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}