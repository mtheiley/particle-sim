#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>

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
#include "gravity.hpp"

void generate_particle(std::vector<Particle*>& particles) {
    Particle* p = new Particle(1.0f, {0.0f, 0.0f, 1.0f});
    float xP = ((float)(rand() % 100) / 1000.0f) - 0.1f;
    float yP = ((float)(rand() % 100) / 1000.0f) + 0.5f;

    p->setPosition({xP, yP, 0.0f});

    particles.push_back(p);
}

int main() {

    size_t width = 640;
    size_t height = 480;
    Window window(width, height, "Particle Sim");
    window.selectWindow();

    opengl::loadGlad();
    opengl::enableDebug();

    ShaderFile vertexShaderFile("../src/shader/vertex_shader.glsl");
    ShaderFile pixelShaderFile("../src/shader/pixel_shader.glsl");

    Shader vertexShader(opengl::ShaderType::VERTEX, vertexShaderFile);
    Shader pixelShader(opengl::ShaderType::PIXEL, pixelShaderFile);

    ShaderProgram shaderProgram({vertexShader.getID(), pixelShader.getID()});
    shaderProgram.selectShaderProgram();

    std::vector<Particle*> particles;

    Particle* p = new Particle(1.0f, {1.0f, 1.0f, 0.0f});
    particles.push_back(p);

    srand(time(NULL));

    size_t NUM_PARTICLES = 1000;
    size_t PARTICLE_SPAWN_DELAY = 500; //milliseconds

    size_t i = 0;
    std::chrono::steady_clock::time_point prev = std::chrono::steady_clock::now();

    while (window.isRunning()) {
        window.clear();

        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(prev - now).count();
        if(i < NUM_PARTICLES && timeElapsed > PARTICLE_SPAWN_DELAY) {
            generate_particle(particles);
            prev = now;
            i++;
        }

        for(Particle* particlePtr : particles) {
            particlePtr->update();
        }

        collision::checkCollisions(particles);
        collision::checkOutOfBounds(particles, 1.0f, 1.0f);
        gravity::apply(particles);

        window.update();
    }

    opengl::terminate();
}