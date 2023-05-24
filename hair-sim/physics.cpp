#include "physics.h"
#include <stdlib.h>

HairStrand createHairStrand(int numVertices, int numSprings) {
    HairStrand strand;
    strand.numVertices = numVertices;
    strand.numSprings = numSprings;

    // Allocate memory for vertices and springs
    //strand.vertices = new Vertex[numVertices];
    strand.springs = new Spring[numSprings];

    // Initialize vertices and springs

    return strand;
}


void destroyHairStrand(HairStrand& strand) {
    // Free memory
    //delete[] strand.numVertices;
    delete[] strand.springs;
}



void applyForces(Vertex* hairVertices, int numVertices, float gravity, const glm::vec3& windDirection, float windStrength) {
    // Apply gravitational force to each hair vertex
    for (int i = 0; i < numVertices; ++i) {
        hairVertices[i].position.y -= gravity; // Assuming y-axis is the vertical axis
    }

    // Apply wind force to each hair vertex based on wind direction and strength
    for (int i = 0; i < numVertices; ++i) {
        hairVertices[i].position += windDirection * windStrength;
    }
}

void calculateSpringForces(const Vertex* hairVertices, int numVertices, float springStiffness, float restLength, std::vector<glm::vec3>& springForces) {
    // Calculate spring forces between adjacent hair vertices
    springForces.clear();
    for (int i = 1; i < numVertices; ++i) {
        const glm::vec3& currentPos = hairVertices[i].position;
        const glm::vec3& previousPos = hairVertices[i - 1].position;
        glm::vec3 springForce = springStiffness * (currentPos - previousPos) * (glm::length(currentPos - previousPos) - restLength);
        springForces.push_back(springForce);
    }
}

void applyDampingForces(Vertex* hairVertices, int numVertices, float dampingCoefficient) {
    // Apply damping forces to each hair vertex based on its velocity
    for (int i = 0; i < numVertices; ++i) {
        hairVertices[i].position -= dampingCoefficient * hairVertices[i].position;
    }
}

void integrate(Vertex* hairVertices, int numVertices, float timeStep) {
    // Perform numerical integration (e.g., Euler integration) to update positions and velocities
    for (int i = 0; i < numVertices; ++i) {
        // Update position using velocity and time step
        hairVertices[i].position += hairVertices[i].velocity * timeStep;

        // Update velocity (e.g., by applying external forces or constraints)
        // ...
    }
}

void updateHair(Vertex* hairVertices, int numVertices, float gravity, const glm::vec3& windDirection, float windStrength, float springStiffness, float restLength, float dampingCoefficient, float timeStep) {
    // Apply external forces (e.g., gravity, wind)
    applyForces(hairVertices, numVertices, gravity, windDirection, windStrength);

    // Calculate spring forces
    std::vector<glm::vec3> springForces;
    calculateSpringForces(hairVertices, numVertices, springStiffness, restLength, springForces);

    // Apply spring forces
    for (int i = 1; i < numVertices; ++i) {
        glm::vec3& currentPos = hairVertices[i].position;
        glm::vec3& previousPos = hairVertices[i - 1].position;
        glm::vec3& currentVelocity = hairVertices[i].velocity;
        glm::vec3& previousVelocity = hairVertices[i - 1].velocity;

        // Update velocities based on spring forces and damping
        glm::vec3 springForce = springForces[i - 1];
        currentVelocity += (springForce / hairVertices[i].mass + gravity) * timeStep;
        previousVelocity -= (springForce / hairVertices[i].mass + gravity) * timeStep;

        // Apply damping forces
        currentVelocity -= dampingCoefficient * currentVelocity * timeStep;
        previousVelocity -= dampingCoefficient * previousVelocity * timeStep;

        // Update positions using velocities
        currentPos += currentVelocity * timeStep;
        previousPos += previousVelocity * timeStep;
    }
}