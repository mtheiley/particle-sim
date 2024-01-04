#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "opengl.hpp"

class GLFWwindow;

class Window {
public:
    Window(unsigned width, unsigned height, std::string title) :
        width(width), height(height) {
        
        window = opengl::createWindow(width, height, title);
    }

    void selectWindow() {
        opengl::selectWindow(window);
    }

    bool isRunning() {
        return !opengl::shouldWindowClose(window);
    }

    void clear() {
        opengl::clearWindow();
    }

    void update() {
        opengl::swapBuffers(window);
        opengl::pollEvents();
    }

private:
    
    unsigned width;
    unsigned height;

    GLFWwindow* window;
};

#endif //WINDOW_H