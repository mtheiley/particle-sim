#ifndef MESH_H
#define MESH_H

#include <vector>
#include <cstdint>
#include <cstdlib>
#include <cassert>

using VertexData = float*;
using IndexData = uint32_t*;

template <typename T>
concept isMesh = requires(T t) {
    []<typename V>(T t) {
        VertexData vertexData = t.getVertexData();
        IndexData indexData = t.getIndexData();
    };
};

class Mesh {
public:

    Mesh() {

    }

    Mesh(std::vector<std::vector<float>> vertexData, std::vector<uint32_t> indexData) {
        setVertexData(vertexData);
        setIndexData(indexData);
    }

    Mesh(Mesh&& other) {
        deepCopy(other);
    }

    Mesh(Mesh& other) {
        deepCopy(other);
    }

    Mesh& operator=(Mesh& other) {
        deepCopy(other);
        return *this;
    }

    VertexData getVertexData() {
        return vertexData;
    }

    IndexData getIndexData() {
        return indexData;
    }

    size_t getNumVerticies() {
        return dim.first;
    }

    size_t getNumIndicies() {
        return numIndicies;
    }

    size_t getVertexDataSize() {
        return vertexDataSize;
    }

    size_t getIndexDataSize() {
        return indexDataSize;
    }

private:
    void deepCopy(Mesh& other) {
        dim = other.dim;
        vertexData = new float[dim.first * dim.second];
        vertexDataSize = other.vertexDataSize;

        for(size_t i = 0; i < dim.first * dim.second; ++i) {
            vertexData[i] = other.vertexData[i];
        }

        numIndicies = other.numIndicies;
        indexData = new uint32_t[numIndicies];
        indexDataSize = other.indexDataSize;

        for(size_t i = 0; i < numIndicies; ++i) {
            indexData[i] = other.indexData[i];
        }
    }

    void setVertexData(std::vector<std::vector<float>>& other) {
        assert(other.size() > 0);
        assert(other[0].size() > 0);
        
        
        dim.first = other.size();
        dim.second = other[0].size();

        vertexData = new float[dim.first * dim.second];
        vertexDataSize = dim.first * dim.second * sizeof(float);

        for(size_t i = 0; i < dim.first; ++i) {
            size_t vertexDataSize = other[i].size();
            assert(dim.second == vertexDataSize);

            for(size_t j = 0; j < dim.second; ++j) {
                vertexData[j + (i*dim.second)] = other[i][j];
            }
        }
    }

    void setIndexData(std::vector<uint32_t>& other) {
        assert(other.size() > 0);
        
        numIndicies = other.size();
        indexData = new uint32_t[other.size()];
        indexDataSize = other.size() * sizeof(uint32_t);

        for(size_t i = 0; i < other.size(); ++i) {
            indexData[i] = other[i];
        }
    }

    VertexData vertexData;
    IndexData indexData;
    std::pair<size_t, size_t> dim;
    size_t numIndicies = 0;
    size_t vertexDataSize = 0;
    size_t indexDataSize = 0;
};

#endif //MESH_H