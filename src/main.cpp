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
#include "particle.hpp"
#include "collision.hpp"

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
    
    //Drawable polygon1(mesh4);
    //Drawable polygon2(mesh4);
    //polygon1.setPosition({0.0f, 1.0f, 0.0f});
    //polygon2.setPosition({1.0f, 0.0f, 0.0f});

    std::vector<Particle*> particles;

    Particle p1(1.0f, {1.0f, 0.0f, 0.0f}); //1 RED
    Particle p2(1.0f, {0.0f, 1.0f, 0.0f}); //2 GREEN
    Particle p3(1.0f, {0.0f, 0.0f, 1.0f}); //3 BLUE
    Particle p4(1.0f, {1.0, 0.5f, 0.0f}); //4 ORANGE

    particles.push_back(&p1);
    particles.push_back(&p2);
    particles.push_back(&p3);
    particles.push_back(&p4);

    p1.setPosition({-1.0f, 0.0f, 0.0f});
    p1.setVelocity({0.001f, 0.0f, 0.0f});
    
    p2.setPosition({1.0f, 0.0f, 0.0f});
    p2.setVelocity({-0.001f, 0.0f, 0.0f});

    p3.setPosition({0.0f, -1.0f, 0.0f});
    p3.setVelocity({0.0f, 0.001f, 0.0f});
    
    p4.setPosition({0.0f, 1.0f, 0.0f});
    //p4.setVelocity({0.0f, -0.001f, 0.0f});

    while (window.isRunning()) {
        window.clear();

        for(Particle* particlePtr : particles) {
            particlePtr->update();
        }

        collision::checkCollisions(particles);
    
        window.update();
    }

    opengl::terminate();
}