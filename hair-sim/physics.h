#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include "model.h"
#include <vector>
#include <glm/glm.hpp>

typedef struct {
    float position[3];
    float velocity[3];
    float mass;
} vrtx;

typedef struct {
    int vertexIndex1;
    int vertexIndex2;
    float restLength;
    float stiffness;
} Spring;

typedef struct {
    std::vector<Vertex> vertices;
    Spring* springs;
    int numVertices;
    int numSprings;
} HairStrand;

HairStrand createHairStrand(int numVertices, int numSprings);

void destroyHairStrand(HairStrand& strand);

void applyForces(Vertex* hairVertices, int numVertices, float gravity, const glm::vec3& windDirection, float windStrength);

void calculateSpringForces(const Vertex* hairVertices, int numVertices, float springStiffness, float restLength, std::vector<glm::vec3>& springForces);

void applyDampingForces(Vertex* hairVertices, int numVertices, float dampingCoefficient);

void integrate(Vertex* hairVertices, int numVertices, float timeStep);

void updateHair(Vertex* hairVertices, int numVertices, float gravity, const glm::vec3& windDirection, float windStrength, float springStiffness, float restLength, float dampingCoefficient, float timeStep);

#endif // PHYSICS_H