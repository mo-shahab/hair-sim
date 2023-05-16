#pragma once
#ifndef RENDERING_H
#define RENDERING_H

#include "model.h"
#include "shaderUtils.h"

extern unsigned char currentKey;
void processKeyboardInput(unsigned char key, int x, int y);
void processKeyboardRelease(unsigned char key, int x, int y);

// Function to render the scene
void renderScene(const std::vector<Vertex>& vertices, GLuint shaderProgram, float aspectRatio);


#endif // RENDERING_H
