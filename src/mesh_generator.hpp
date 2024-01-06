#ifndef MESH_GENERATOR_H
#define MESH_GENERATOR_H

#include <cmath>
#include <stdexcept>
#include "mesh.hpp"

namespace mesh_generate {
    Mesh create_polygon(float radius, size_t sides) {
        if(sides < 3) throw new std::runtime_error("cannot have polygon with less than 3 sides");
        
        std::vector<std::vector<float>> vertexData;
        vertexData.push_back({0.0f, 0.0f, 0.0f});

        for(size_t i = 0; i < sides; ++i) {
            double angleRadians = i*2*3.14/sides;

            float x = radius*cos(angleRadians);
            float y = radius*sin(angleRadians);
        
            vertexData.push_back({x, y, 0.0f});
        }

        std::vector<uint32_t> indexData;
        for(size_t i = 1; i < sides; ++i) {
            indexData.push_back(0);
            indexData.push_back(i);
            indexData.push_back(i+1);
        }
        indexData.push_back(0);
        indexData.push_back(sides);
        indexData.push_back(1);

        Mesh mesh(vertexData, indexData);

        return mesh;
    }

};

#endif //MESH_GENERATOR