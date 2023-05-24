#pragma once
#ifndef RENDERING_H
#define RENDERING_H

#include "model.h"
#include "shaderUtils.h"

extern unsigned char currentKey;
void processKeyboard(unsigned char key, int x, int y);
void processKeyboardRelease(unsigned char key, int x, int y);
void processMouseMovement(int x, int y);
void processMouseButton(int button, int state, int x, int y);

// Function to render the scene
void renderScene(const std::vector<Vertex>& vertices, GLuint shaderProgram, float aspectRatio);


#endif // RENDERING_H
