#pragma once
#include <GLFW/glfw3.h>

class Window {
    private:
        GLFWwindow* window;
    public:
        ~Window() {
            glfwTerminate();
        }
        void Init(unsigned short width, unsigned short height, const char* title);
};