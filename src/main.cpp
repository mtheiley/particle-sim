#include <iostream>

#include "opengl.hpp"
#include "window.hpp"
#include "shader_file.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include "drawable.hpp"
#include "mesh.hpp"

int main() {

    Window window(640, 480, "Particle Sim");
    window.selectWindow();

    opengl::loadGlad();
    opengl::enableDebug();

    ShaderFile vertexShaderFile("../src/shader/vertex_shader.glsl");
    ShaderFile pixelShaderFile("../src/shader/pixel_shader.glsl");

    Shader vertexShader(opengl::ShaderType::VERTEX, vertexShaderFile);
    Shader pixelShader(opengl::ShaderType::PIXEL, pixelShaderFile);

    ShaderProgram shaderProgram({vertexShader.getID(), pixelShader.getID()});
    shaderProgram.selectShaderProgram();

    Mesh mesh1(
        {{-1.0f, -1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f},
        {0.0f,  1.0f, 0.0f}},

        {0, 1, 2}
    );

    Mesh mesh2(
        {{-1.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f,  -1.0f, 0.0f}},

        {0, 1, 2}
    );
    
    Drawable upTriangle(mesh1);
    Drawable downTriangle(mesh2);

    while (window.isRunning()) {
        
        window.clear();

        upTriangle.draw();
        downTriangle.draw();
        
        window.update();
    }

    opengl::terminate();
}