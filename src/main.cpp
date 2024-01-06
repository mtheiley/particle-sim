#include <iostream>
#include <cmath>

#include "opengl.hpp"
#include "window.hpp"
#include "shader_file.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include "drawable.hpp"
#include "mesh.hpp"
#include "mesh_generator.hpp"

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

    Mesh mesh4 = mesh_generate::create_polygon(0.2, 10);
    
    Drawable polygon1(mesh4);
    Drawable polygon2(mesh4);
    polygon1.setPosition({0.0f, 1.0f, 0.0f});
    polygon2.setPosition({1.0f, 0.0f, 0.0f});

    float i = 1.0f;
    while (window.isRunning()) {

        float j = cos(i);

        window.clear();

        polygon1.draw();
        polygon1.setPosition({0.0f, j, 0.0f});

        polygon2.draw();
        polygon2.setPosition({j, 0.0f, 0.0f});
    
        window.update();

        i -= 0.01;
    }

    opengl::terminate();
}