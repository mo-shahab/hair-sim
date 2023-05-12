#pragma once
#ifndef RENDERING_H
#define RENDERING_H

#include "model.h"

// Function to create and bind the VAO and VBO
void setupBuffers(const std::vector<Vertex>& vertices);

// Function to render the scene
void renderScene(const std::vector<Vertex>& vertices);

#endif // RENDERING_H
