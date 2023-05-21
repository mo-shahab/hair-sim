#include "physics.h"
#include <stdlib.h>

HairStrand createHairStrand(int numVertices, int numSprings) {
    HairStrand strand;
    strand.numVertices = numVertices;
    strand.numSprings = numSprings;

    // Allocate memory for vertices and springs
    strand.vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));
    strand.springs = (Spring*)malloc(numSprings * sizeof(Spring));

    // Initialize vertices and springs

    return strand;
}

void destroyHairStrand(HairStrand& strand) {
    // Free memory
    free(strand.vertices);
    free(strand.springs);
}

void applyForces(std::vector<Vertex>& hairVertices, float gravity, const glm::vec3& windDirection, float windStrength) {
    // Apply gravitational force to each hair vertex
    for (auto& vertex : hairVertices) {
        vertex.position.y -= gravity; // Assuming y-axis is the vertical axis
    }

    // Apply wind force to each hair vertex based on wind direction and strength
    for (auto& vertex : hairVertices) {
        vertex.position += windDirection * windStrength;
    }
}

void calculateSpringForces(const std::vector<Vertex>& hairVertices, float springStiffness, float restLength, std::vector<glm::vec3>& springForces) {
    // Calculate spring forces between adjacent hair vertices
    for (size_t i = 1; i < hairVertices.size(); ++i) {
        const glm::vec3& currentPos = hairVertices[i].position;
        const glm::vec3& previousPos = hairVertices[i - 1].position;
        glm::vec3 springForce = springStiffness * (currentPos - previousPos) * (glm::length(currentPos - previousPos) - restLength);
        springForces.push_back(springForce);
    }
}

void applyDampingForces(std::vector<Vertex>& hairVertices, float dampingCoefficient) {
    // Apply damping forces to each hair vertex based on its velocity
    for (auto& vertex : hairVertices) {
        vertex.position -= dampingCoefficient * vertex.position;
    }
}

void integrate(std::vector<Vertex>& hairVertices, float timeStep) {
    // Perform numerical integration (e.g., Euler integration) to update positions and velocities
    for (auto& vertex : hairVertices) {
        // Update position using velocity and time step
        vertex.position += vertex.velocity * timeStep;

        // Update velocity (e.g., by applying external forces or constraints)
        // ...
    }
}

void updateHair(std::vector<Vertex>& hairVertices, float gravity, const glm::vec3& windDirection, float windStrength, float springStiffness, float restLength, float dampingCoefficient, float timeStep) {
    // Apply external forces (e.g., gravity, wind)
    applyForces(hairVertices, gravity, windDirection, windStrength);

    // Calculate spring forces
    std::vector<glm::vec3> springForces;
    calculateSpringForces(hairVertices, springStiffness, restLength, springForces);

    // Apply spring forces
    for (size_t i = 1; i < hairVertices.size(); ++i) {
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