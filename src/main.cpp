#include <iostream>
#include <ostream>
#include <window.hpp>

int main() {
    try {
        Window engine;
        engine.Init(100,100,"Hello");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}