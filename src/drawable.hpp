#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>
#include "opengl.hpp"
#include "mesh.hpp"
#include "vertex.hpp"

//Dummy Object to test drawing

class Drawable {
public:
    Drawable() {

    }

    Drawable(Mesh mesh) {
        this->mesh = mesh;
        drawableId = opengl::createDrawable(mesh);
    }

    void draw() {
        opengl::draw(drawableId, mesh.getNumIndicies());
    }

private:
    opengl::DrawableID drawableId = 0;
    Mesh mesh;
};

#endif //DRAWABLE_H