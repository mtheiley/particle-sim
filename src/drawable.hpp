#ifndef DRAWABLE_H
#define DRAWABLE_H

//#include <glm/glm.hpp>
#include <array> 
#include "opengl.hpp"
#include "mesh.hpp"
#include "shader_program.hpp"

//Dummy Object to test drawing

class Drawable {
private:
    static constexpr size_t POSITION_SIZE = 3;
    static constexpr size_t COLOUR_SIZE = 3;

public:
    Drawable() {

    }

    Drawable(Mesh mesh) {
        this->mesh = mesh;
        drawableId = opengl::createDrawable(mesh);
    }

    void setColour(float(&&colour)[COLOUR_SIZE]) {
        setColour(colour);
    }

    void setColour(float(&colour)[COLOUR_SIZE]) {
        for(size_t i = 0; i < COLOUR_SIZE; ++i) {
            this->colour[i] = colour[i];
        }
    }

    void setPosition(float(&&position)[POSITION_SIZE]) {
        setPosition(position);
    }

    void setPosition(float(&position)[POSITION_SIZE]) {
        for(size_t i = 0; i < POSITION_SIZE; ++i) {
            this->position[i] = position[i];
        }
    }

    const std::array<float, POSITION_SIZE>& getPosition() {
        return position;
    }

    void draw() {
        opengl::setUniformValue(opengl::getUniformId(opengl::POSITION_UNIFORM_NAME), position);
        opengl::setUniformValue(opengl::getUniformId(opengl::COLOUR_UNIFORM_NAME), colour);
        opengl::draw(drawableId, mesh.getNumIndicies());
    }

private:
    std::array<float, POSITION_SIZE> position = {0.0f, 0.0f, 0.0f};
    std::array<float, COLOUR_SIZE> colour = {1.0f, 0.0f, 0.0f};
    opengl::DrawableID drawableId = 0;
    Mesh mesh;
};

#endif //DRAWABLE_H