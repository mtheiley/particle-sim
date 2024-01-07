#ifndef COLLISION_H
#define COLLISION_H

#include <cmath>
#include <iostream>

#include "particle.hpp"

namespace collision {
    
    float ENERGY_LOSS = 0.01;
    float COLLIDE_ENERGY_LOSS = 0.01;

    float calculateVelocity(float unitDirection, float speed) {  
        float ABSOLUTE_LIMIT = 0.0000000000000001;

        float total = unitDirection * speed;
        float totalAbs = total;
        if(total < 0) {
            totalAbs = -total;
        }
        
        if(totalAbs < ABSOLUTE_LIMIT) {
            total = 0;
        }
        return total;
    }

    std::array<float, 3> calculateUnitVector(std::array<float, 3> vec) {
        float speed = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    
        std::array<float, 3> unitVector;
        unitVector.fill(0);

        if(speed > 0) {
            unitVector[0] = vec[0] / speed;
            unitVector[1] = vec[1] / speed;
            unitVector[2] = vec[2] / speed;
        }

        return unitVector;
    }

    void moveParticlesAppart(Particle& left, Particle& right, float overlapDistance) {
        const auto& lV = left.getVelocity();
        const auto& rV = right.getVelocity();
        
        std::array<float, 3> ulV = calculateUnitVector(lV);
        std::array<float, 3> urV = calculateUnitVector(rV);

        const auto& lP = left.getPosition();
        const auto& rP = right.getPosition();
        const float offset = overlapDistance*1.1;

        left.setPosition({
            lP[0] - ulV[0]*(offset),
            lP[1] - ulV[1]*(offset),
            lP[2] - ulV[2]*(offset)
        });

        right.setPosition({
            rP[0] - urV[0]*(offset),
            rP[1] - urV[1]*(offset),
            rP[2] - urV[2]*(offset)
        });

    }

    void handleCollide(Particle& left, Particle& right) {
        const auto& lP = left.getPosition();
        const auto& rP = right.getPosition();

        std::array<float, 3> nlV = {
            lP[0] - rP[0],
            lP[1] - rP[1],
            lP[2] - rP[2]
        };

        std::array<float, 3> nrV = {
            rP[0] - lP[0],
            rP[1] - lP[1],
            rP[2] - lP[2]
        };

        std::array<float, 3> unlV = calculateUnitVector(nlV);
        std::array<float, 3> unrV = calculateUnitVector(nrV);

        const auto& lV = left.getVelocity();
        const auto& rV = right.getVelocity();

        float lVSpeed = sqrt(lV[0]*lV[0] + lV[1]*lV[1] + lV[2]*lV[2]);
        float rVSpeed = sqrt(rV[0]*rV[0] + rV[1]*rV[1] + rV[2]*rV[2]);

        float lspeed = ((lVSpeed + rVSpeed) / 2) * (1.0f - COLLIDE_ENERGY_LOSS);
        float rspeed = ((rVSpeed + lVSpeed) / 2) * (1.0f - COLLIDE_ENERGY_LOSS);

        left.setVelocity({
            calculateVelocity(unlV[0], lspeed),
            calculateVelocity(unlV[1], lspeed),
            calculateVelocity(unlV[2], lspeed)
        });

        right.setVelocity({
            calculateVelocity(unrV[0], rspeed),
            calculateVelocity(unrV[1], rspeed),
            calculateVelocity(unrV[2], rspeed)
        });
    }

    float calculateDistance(const std::array<float, 3>& left, const std::array<float, 3>& right) {
        float x = right[0] - left[0];
        float y = right[1] - left[1];
        float z = right[2] - left[2];

        return sqrt(x*x + y*y + z*z);
    }

    void checkCollide(Particle& left, Particle& right) {
        float distance = calculateDistance(left.getPosition(), right.getPosition());
        float collideDistance = left.getRadius() + right.getRadius();
        
        bool collided = (distance < collideDistance) && left != right;
        if(collided) {
            //moveParticlesAppart(left, right, collideDistance-distance); //OPTIONAL - leads to weird jumpy behaviour
            handleCollide(left, right);
        }
    }

    void checkCollideBoundary(Particle& particle, float width, float height) {
        const auto& pos = particle.getPosition();
        const float r = particle.getRadius();
        const auto& vel = particle.getVelocity();
        
        float nVel[3] = {
            vel[0], vel[1], vel[2]
        };

        float nPos[3] = {
            pos[0], pos[1], pos[2]
        };

        float offset = 0.0000000000;

        const auto& lV = particle.getPosition();

        if(pos[0] + r > width) {
            nVel[0] = -vel[0];
            nVel[0] *= 1.0f - ENERGY_LOSS;
            nPos[0] = width - (r + offset);
        } else if (pos[0] - r < -width) {
            nVel[0] = -vel[0];
            nVel[0] *= 1.0f - ENERGY_LOSS;
            nPos[0] = -width + (r + offset);
        }

        if(pos[1] + r > height) {
            nVel[1] = -vel[1];
            nVel[1] *= 1.0f - ENERGY_LOSS;
            nPos[1] = height - (r + offset);
        } else if (pos[1] - r < -height) {
            nVel[1] = -vel[1];
            nVel[1] *= 1.0f - ENERGY_LOSS;
            nPos[1] = -height + (r + offset);
        }

        particle.setPosition(nPos);
        particle.setVelocity(nVel);
    }

    void checkOutOfBounds(std::vector<Particle*> particles, float width, float height) {
        for(Particle* current : particles) {
            checkCollideBoundary(*current, width, height);
        }
    }

    void checkCollisions(std::vector<Particle*> particles) {
        for(Particle* current : particles) {
            for(Particle * other : particles) {
                checkCollide(*current, *other);
            }
        }
    }

};

#endif //COLLISION_H