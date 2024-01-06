#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>
#include "opengl.hpp"
#include "mesh.hpp"
#include "shader_program.hpp"

//Dummy Object to test drawing

class Drawable {
private:
    static constexpr size_t POSITION_SIZE = 3;

public:
    Drawable() {

    }

    Drawable(Mesh mesh) {
        this->mesh = mesh;
        drawableId = opengl::createDrawable(mesh);
    }

    void setPosition(float(&&position)[POSITION_SIZE]) {
        setPosition(position);
    }

    void setPosition(float(&position)[POSITION_SIZE]) {
        for(size_t i = 0; i < POSITION_SIZE; ++i) {
            this->position[i] = position[i];
        }
    }

    void draw() {
        opengl::setUniformValue(opengl::getUniformId(opengl::POSITION_UNIFORM_NAME), position);
        opengl::draw(drawableId, mesh.getNumIndicies());
    }

private:
    float position[3] = {0.0f, 0.0f, 0.0f};
    opengl::DrawableID drawableId = 0;
    Mesh mesh;
};

#endif //DRAWABLE_H