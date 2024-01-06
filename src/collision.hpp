#ifndef COLLISION_H
#define COLLISION_H

#include <cmath>
#include <iostream>

#include "particle.hpp"

namespace collision {
    void handleCollide(Particle& left, Particle& right) {
        //const auto& leftVelocity = left.getVelocity();
        //const auto& rightVelocity = right.getVelocity();

        std::cout << "COLLIDE!!!" << std::endl;
    }

    float calculateDistance(const std::array<float, 3>& left, const std::array<float, 3>& right) {
        float x = right[0] - left[0];
        float y = right[1] - left[1];
        float z = right[2] - left[2];

        return sqrt(x*x + y*y + z*z);
    }

    bool checkCollide(Particle& left, Particle& right) {
        float distance = calculateDistance(left.getPosition(), right.getPosition());
        float collideDistance = left.getRadius() + right.getRadius();
        
        return (distance < collideDistance) && left != right;
    }

    void checkCollisions(std::vector<Particle*> particles) {
        for(Particle* current : particles) {
            for(Particle * other : particles) {
                if(checkCollide(*current, *other)) {
                    handleCollide(*current, *other);
                }
            }
        }
    }

};

#endif //COLLISION_H