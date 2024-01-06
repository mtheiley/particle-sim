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
    static constexpr char POSITION_UNIFORM_NAME[] = "offset";

    using ShaderID = uint32_t;
    using ShaderProgramID = uint32_t;
    using DrawableID = uint32_t;
    using UniformID = uint32_t;

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

    static UniformID getUniformId(std::string uniformName);
    
    template <typename T>
    static void setUniformValue(UniformID uniformId, T&& uniformData) {
        setUniformHelper(uniformId, uniformData);
    }

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
    //TODO will need more uniform helpers if we use matricies
    static void setUniformHelper(UniformID uniformId, float(&values)[4]);
    static void setUniformHelper(UniformID uniformId, float(&values)[3]);
    static void setUniformHelper(UniformID uniformId, float(&values)[2]);

    static void setUniformHelper(UniformID uniformId, float value);

    opengl();
    static opengl instance;
    static ShaderProgramID currentlySelectedShader;
};

#endif //OPEN_GL_H