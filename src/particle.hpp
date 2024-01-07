#ifndef PARTICLE_H
#define PARTICLE_H

#include "drawable.hpp"
#include "mesh_generator.hpp"

class Particle {
private:

    static size_t nextId;
    size_t id = 0; 
    static constexpr size_t COLOUR_SIZE = 3;
    static constexpr size_t POSITION_SIZE = 3;
    static constexpr size_t VELOCITY_SIZE = 3;
    static constexpr size_t PARTICLE_ROUNDNESS = 10;
    static constexpr float PARTICLE_SIZE = 0.02;

    std::array<float, 3> velocity = {0.0f, 0.0f, 0.0f};
    float mass = 0;

    Drawable drawable = mesh_generate::create_polygon(PARTICLE_SIZE, PARTICLE_ROUNDNESS);

public:
    Particle(float mass, float(&&colour)[COLOUR_SIZE])
     : mass(mass) {        
        id = nextId;
        nextId++;

        drawable.setColour(colour);
    }

    bool operator==(Particle& other) {
        return this->id == other.id;
    }

    void setPosition(float(&&position)[POSITION_SIZE]) {
        setPosition(position);
    }

    void setPosition(float(&position)[POSITION_SIZE]) {
        drawable.setPosition(position);
    }

    const std::array<float, 3>& getPosition() {
        return drawable.getPosition();
    }

    void setVelocity(float(&&velocity)[VELOCITY_SIZE]) {
        setVelocity(velocity);
    }

    void setVelocity(float(&velocity)[VELOCITY_SIZE]) {
        for(size_t i = 0; i < VELOCITY_SIZE; ++i) {
            this->velocity[i] = velocity[i];
        }
    }

    const float getRadius() {
        return PARTICLE_SIZE;
    }

    const std::array<float, 3>& getVelocity() {
        return velocity;
    }

    size_t getId() {
        return id;
    }

    void update() {
        const auto& position = drawable.getPosition(); 
        drawable.setPosition({
            position[0] + velocity[0],
            position[1] + velocity[1],
            position[2] + velocity[2]
        });
        drawable.draw();
    }

};

size_t Particle::nextId = 0;

#endif //PARTICLE_H