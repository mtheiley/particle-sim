#ifndef OPEN_GL_H
#define OPEN_GL_H

#include <cstdint>
#include <string>
#include <stdexcept>

#include <glm/glm.hpp>

#include "mesh.hpp"

struct GLFWwindow;

class opengl {
public:

    using ShaderID = uint32_t;
    using ShaderProgramID = uint32_t;
    using DrawableID = uint32_t;

    enum class ShaderType {
        VERTEX,
        PIXEL
    };

    static ShaderID createShader(ShaderType shaderType);
    static void compileShader(ShaderID shaderId, std::string shaderSource);
    static ShaderProgramID createShaderProgram();
    static void attachShader(ShaderProgramID shaderProgramId, ShaderID shaderIDList);
    static void linkShader(ShaderProgramID shaderProgramId);
    static void selectShaderProgram(ShaderProgramID shaderProgramId);

    static DrawableID createDrawable(Mesh& mesh);
    static void draw(DrawableID drawableId, uint32_t totalIndicies);

    static void enableDebug();

    //TODO move window related helper functions to new class glfw?
    static GLFWwindow* createWindow(unsigned width, unsigned height, std::string title);
    static void selectWindow(GLFWwindow* window);
    static bool shouldWindowClose(GLFWwindow* window);
    static void setViewPort(int32_t xPos, int32_t yPos, uint32_t width, uint32_t height);
    static void clearWindow();
    static void swapBuffers(GLFWwindow* window);
    static void pollEvents();

    static void loadGlad();
    static void terminate();

private:
    opengl();
    static opengl instance;
};

#endif //OPEN_GL_H