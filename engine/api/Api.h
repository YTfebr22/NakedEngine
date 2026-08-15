#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
// #include "glad/glad.h"
#include <GLFW/glfw3.h>


class Window {
private:
    const std::string TITLE = "GLFW Window";
    const int32_t WIDTH = 640;
    const int32_t HEIGHT = 480;
    const bool FULLSCREEN = false;

    GLFWwindow* mwindow;
public:
    Window() {
        mwindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), (!FULLSCREEN) ? nullptr : glfwGetPrimaryMonitor(), nullptr);
        if (WIDTH <= 0 || HEIGHT <= 0) {
            throw std::runtime_error("GLFW Error: Height and width must be greater than 0");
        } else if (!mwindow) {
                throw std::runtime_error("Failed to create GLFW Window");
        }
    };

    ~Window() {
        glfwTerminate();
    }

    void ContextCurrent() {
        glfwMakeContextCurrent(mwindow);
    }

    void loop() {
        while (!glfwWindowShouldClose(mwindow)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(mwindow);
            glfwPollEvents();
        }
    }
};

class Renderer;
class Shader {
private:
    std::stringstream ss;
public:
    std::string ReadShaderFromFile(const std::string& FileName) {
        std::ifstream file("/home/twst/git/NakedEngine/engine/Shaders/" + FileName);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open shader file");
        }
        ss << file.rdbuf();
        return ss.str();
    }
};