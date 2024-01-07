#ifndef GRAVITY_H
#define GRAVITY_H

#include <vector>
#include "particle.hpp"

namespace gravity {

    float calculateAcceleration(float init) {
        float TERMINAL_VELOCITY = 0.5f;
        float ACCELERATION = 0.0001f;

        float total = init - ACCELERATION;
        if(total < -TERMINAL_VELOCITY) {
            total = -TERMINAL_VELOCITY;
        }

        return total;
    }

    void accelerateDown(Particle& particle) {
        const auto& vel = particle.getVelocity();
        particle.setVelocity({
            vel[0],
            calculateAcceleration(vel[1]),
            vel[2]
        });
    }

    void apply(std::vector<Particle*> particles) {
        for(Particle* current : particles) {
            accelerateDown(*current);
        }
    }
}

#endif //GRAVITY_H