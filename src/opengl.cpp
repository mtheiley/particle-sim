#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstring>

#include "opengl.hpp"
#include "window_exception.hpp"
#include "shader_exception.hpp"

static void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
         glfwSetWindowShouldClose(window, GLFW_TRUE);
}

opengl opengl::instance = opengl();

opengl::opengl() {
 
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit()) {
        throw new WindowException("unable to initialise GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    std::cout << "Loaded OpenGL" << std::endl;
}

static GLenum convertShaderType(opengl::ShaderType shaderType) {
    switch(shaderType) {
        case opengl::ShaderType::VERTEX:
            return GL_VERTEX_SHADER;
        case opengl::ShaderType::PIXEL:
            return GL_FRAGMENT_SHADER;
        default:
            throw new ShaderException("unknown shader type");
    }
}

opengl::ShaderID opengl::createShader(ShaderType shaderType) {
    GLenum convertedShaderType = convertShaderType(shaderType);
    return glCreateShader(convertedShaderType);
}

void opengl::compileShader(opengl::ShaderID shaderId, std::string shaderSource) {
    const char* shaderSourceCStr = shaderSource.c_str();

    glShaderSource(shaderId, 1, &shaderSourceCStr, NULL);
    glCompileShader(shaderId);
}

GLFWwindow* opengl::createWindow(unsigned width, unsigned height, std::string title) {
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwSetKeyCallback(window, key_callback); //TODO separate callbacks
    return window;
}

void opengl::selectWindow(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //TODO separate swap interval;
}

void opengl::setViewPort(int32_t xPos, int32_t yPos, uint32_t width, uint32_t height) {
    glViewport(xPos, yPos, width, height);
}

void opengl::clearWindow() {
    glClear(GL_COLOR_BUFFER_BIT);
}

bool opengl::shouldWindowClose(GLFWwindow* window) {
    return glfwWindowShouldClose(window);
}

void opengl::swapBuffers(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void opengl::pollEvents() {
    glfwPollEvents();
}


void opengl::terminate() {
    glfwTerminate();
}

opengl::ShaderProgramID opengl::createShaderProgram() {
    return glCreateProgram();
}

void opengl::attachShader(opengl::ShaderProgramID shaderProgramId, opengl::ShaderID shaderId) {
    glAttachShader(shaderProgramId, shaderId);
}

void opengl::linkShader(opengl::ShaderProgramID shaderProgramId) {
    glLinkProgram(shaderProgramId);
}

void opengl::selectShaderProgram(opengl::ShaderProgramID shaderProgramId) {
    glUseProgram(shaderProgramId);
}

opengl::DrawableID opengl::createDrawable(Mesh& mesh) {

    if(mesh.getNumVerticies() == 0) {
        throw new std::runtime_error("vertex size must be greater then zero");
    }

    if(mesh.getNumIndicies() == 0) {
        throw new std::runtime_error("index size must be greater than zero");
    }

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.getVertexDataSize(), mesh.getVertexData(), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, vVert.size() * sizeof(decltype(mesh)), &vVert[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndexDataSize(), mesh.getIndexData(), GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, vIndex.size() * sizeof(uint32_t), &vIndex[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return vao;
}

void opengl::draw(opengl::DrawableID drawableId, uint32_t totalIndicies) {

    if(drawableId == 0) {
        throw new ShaderException("Drawable id is invalid");
    }

    glBindVertexArray(drawableId);
    glDrawElements(GL_TRIANGLES, totalIndicies, GL_UNSIGNED_INT, 0);
}

void opengl::loadGlad() {
    gladLoadGL();
}

void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

void opengl::enableDebug() {
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
}